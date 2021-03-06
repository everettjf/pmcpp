//
//  main.cpp
//  pmcpp-code
//
//  Created by everettjf on 2019/4/14.
//  Copyright © 2019 everettjf. All rights reserved.
//

#include <iostream>
#include "basis/variadic_template.hpp"
#include "basis/forwarding_reference.hpp"
#include "basis/array_vector.hpp"
#include "basis/deque_test.hpp"
#include "basis/list_test.hpp"
#include "basis/map_set_test.hpp"
#include "usage/serial_task_test.hpp"


int main(int argc, const char * argv[]) {
    
//    variadic_template();
//    forwarding_reference();
//    array_vector();
//    deque_test();
//    list_test();
//    map_set_test();
    
    serial_task_test();
    
    return 0;
}
