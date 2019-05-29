//
//  list_test.cpp
//  pmcpp-code
//
//  Created by everettjf on 2019/5/29.
//  Copyright © 2019 everettjf. All rights reserved.
//

#include "list_test.hpp"
#include <forward_list>
#include <string>
#include <iostream>
#include <list>

template <typename T>
void print_list(T&& t) {
    for (auto & i : t) {
        std::cout << i << ",";
    }
    std::cout << std::endl;
}

void forward_list_test() {
    
    std::forward_list<std::string> words {"one","two","three"};
    print_list(words); // one,two,three,
    
    auto before_begin = words.before_begin();
    words.insert_after(before_begin, "zero");
    print_list(words); // zero,one,two,three,
    
    std::cout << words.front() << std::endl; // zero
    
    words.push_front("-1");
    print_list(words); // -1,zero,one,two,three,

    words.pop_front();
    print_list(words); // zero,one,two,three,
    
    words.reverse();
    print_list(words); // three,two,one,zero,
    
    words.sort();
    print_list(words); // one,three,two,zero,
    
    words.push_front("one");
    print_list(words); // one,one,three,two,zero,

    words.unique();
    print_list(words); // one,three,two,zero,
    
    std::forward_list<int> list1 = { 5,9,0,1,3 };
    std::forward_list<int> list2 = { 8,7,2,6,4 };
    
    list1.sort();
    list2.sort();
    std::cout << "list1:  "; print_list(list1); // list1:  0,1,3,5,9,
    std::cout << "list2:  "; print_list(list2); // list2:  2,4,6,7,8,
    list1.merge(list2);
    std::cout << "merged: "; print_list(list1); // merged: 0,1,2,3,4,5,6,7,8,9,

}


void list_container_test() {
    std::list<int> l = { 7, 5, 16, 8 };
    l.push_front(25);
    print_list(l); // 25,7,5,16,8,

    l.push_back(13);
    print_list(l); // 25,7,5,16,8,13,

    l.pop_front();
    print_list(l); // 7,5,16,8,13,

    l.pop_back();
    print_list(l); // 7,5,16,8,

    auto it = std::find(l.begin(), l.end(), 16);
    if (it != l.end()) {
        l.insert(it, 42); // 找到16，在前面插入42
    }
    print_list(l); // 7,5,42,16,8,
}


void list_test() {
//    forward_list_test();
    
    list_container_test();
}
