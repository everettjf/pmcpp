//
//  serial_task.hpp
//  pmcpp-code
//
//  Created by everettjf on 2019/5/31.
//  Copyright © 2019 everettjf. All rights reserved.
//

#ifndef serial_task_hpp
#define serial_task_hpp


#include <stdio.h>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>

class SerialTask {
public:
    using TaskBody = std::function<void(void)>;
    
    std::queue<TaskBody> _tasks;
    std::mutex _mutex;
    std::condition_variable _condition;
    std::thread _consumer_thread;
public:
    static SerialTask & Instance() {
        static SerialTask o;
        return o;
    }
    
    SerialTask();
    void Consumer();
    void Push(TaskBody&& task);
    
};

#endif /* serial_task_hpp */
