//
//  deque_test.cpp
//  pmcpp-code
//
//  Created by everettjf on 2019/5/14.
//  Copyright © 2019 everettjf. All rights reserved.
//

#include "deque_test.hpp"
#include <deque>
#include <iostream>

template <typename T>
void print_deque(T&& t) {
    for(auto &n : t){
        std::cout << n<< ",";
    }
    std::cout << std::endl;
}

void deque_test(){
    std::deque<int> d = {1,20,3,40,5,60};
    print_deque(d); // 1,20,3,40,5,60,
    
    std::cout << d[0] << "," << d[1] << std::endl; // 1,20
    
    d.push_front(0);
    d.push_back(7);
    
    std::cout << d[0] << "," << d[1] << std::endl; // 0,1
    
    print_deque(d); // 0,1,20,3,40,5,60,7,
    
    d[0] = 100;
    
    print_deque(d); // 100,1,20,3,40,5,60,7,
    
    d.clear();
    d.shrink_to_fit();
}
