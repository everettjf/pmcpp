# C++实现简单的串行任务机制

iOS开发中比较爽的一点就是，可以使用Grand Dispatch Central的dispatch_async。 dispatch_async支持`串行`和`并行`执行block。本文就是使用C++实现一个`串行`任务机制。


话不多说，直接看代码。

# 使用方法

```
SerialTask::Instance().Push([]() {
    std::cout << "task 1" << std::endl;
    usleep(1 * 1000 * 1000);
});
SerialTask::Instance().Push([]() {
    std::cout << "task 2" << std::endl;
});
SerialTask::Instance().Push([]() {
    std::cout << "task 3" << std::endl;
});

```

# 实现

```
// serial_task.h

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

```

```
// serial_task.cpp


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
```

# 讲解

代码很少，但涉及内容不少。涉及到 function、thread、queue、condition_variable、bind、mutex、lock_guard，以及lambda function，还有RAII机制。大家可以自行根据关键词查找资料。


# 代码

https://github.com/everettjf/pmcpp/tree/master/pmcpp-code/pmcpp-code/usage


# 总结


啊，这种入门文章感觉不好写。如果细着写，要写太多。如果粗着写，读者就需要自己查询太多内容。
考虑再三，我决定未来专注于`一些很难查到，或者查到后很难看懂`的知识点。像一些简单的基础知识，就`一水而过`，大家知道有这个东西，并且知道查什么，就好了。 :)





