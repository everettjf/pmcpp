//
//  map_set_test.cpp
//  pmcpp-code
//
//  Created by everettjf on 2019/5/29.
//  Copyright © 2019 everettjf. All rights reserved.
//

#include "map_set_test.hpp"
#include <iostream>
#include <string>

#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

template <typename T>
void print_list(T&& t) {
    for (auto & i : t) {
        std::cout << i << ",";
    }
    std::cout << std::endl;
}

template <typename T>
void print_map(T&& t) {
    for (auto &i : t) {
        std::cout << i.first << ":" << i.second << " , ";
    }
    std::cout << std::endl;
}

void map_set_test() {
    
    // https://zh.cppreference.com/w/cpp/container/set
    std::set<int> s;
    s.insert(1);
    s.insert(1);
    s.insert(2);
    print_list(s);
    
    if (s.find(2) != s.end()) {
        std::cout << "found 2" << std::endl;
    }
    
    // https://zh.cppreference.com/w/cpp/container/map
    std::map<std::string,int> m;
    m["a"] = 1;
    m["b"] = 2;
    m.insert(std::make_pair("c", 3));
    print_map(m);
    
    if (m.find("c") != m.end()) {
        std::cout << "found c" << std::endl;
    }
    
}
