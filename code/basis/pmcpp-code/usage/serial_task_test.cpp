//
//  serial_task_test.cpp
//  pmcpp-code
//
//  Created by everettjf on 2019/5/31.
//  Copyright © 2019 everettjf. All rights reserved.
//

#include "serial_task_test.hpp"
#include "serial_task.hpp"
#include <iostream>
#include <unistd.h>


void serial_task_test() {
    
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

    
    std::cin.get();
}

