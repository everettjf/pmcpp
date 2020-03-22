//
//  serial_task.cpp
//  pmcpp-code
//
//  Created by everettjf on 2019/5/31.
//  Copyright © 2019 everettjf. All rights reserved.
//

#include "serial_task.hpp"


SerialTask::SerialTask() {
    auto thread_body = std::bind(&SerialTask::Consumer,this);
    _consumer_thread = std::thread(thread_body);
}

void SerialTask::Consumer(){
    while(true){
        std::queue<TaskBody> queue;
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _condition.wait(lock, [this]{ return !_tasks.empty();});
            queue = std::move(_tasks);
        }
        
        while(!queue.empty()){
            TaskBody task = queue.front();
            queue.pop();
            
            task();
        }
    }
}

void SerialTask::Push(TaskBody&& task) {
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _tasks.emplace(task);
    }
    _condition.notify_one();
}
