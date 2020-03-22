//
//  variadic-template.cpp
//  pmcpp-code
//
//  Created by everettjf on 2019/4/16.
//  Copyright © 2019 everettjf. All rights reserved.
//

#include "variadic_template.hpp"
#include <iostream>
#include <vector>
using namespace std;

// print parameter count
template <typename ... T>
void print_param_count(T... args) {
    cout << sizeof...(args) << endl;
}

// expand parameters : method 1
void print_params_one() {
    cout << "last" << endl;
}
template <typename T, typename ... Q>
void print_params_one(T first, Q ... others) {
    cout << first << endl;
    print_params_one(others...);
}

// expand parameters : method 2
template <typename T>
void print_arg(T t) {
    cout << t << endl;
}
template <typename ... T>
void print_params_two(T ... args) {
    int arr[] = {(print_arg(args),0)...};
    // or
    //initializer_list<int>{(print_arg(args),0)...};
}

// expand parameters : method 3
template <typename ... T>
void print_params_three(T ... args) {
    initializer_list<int>{
        (
         [&]{ cout << args << endl;}(),
         0
        )...
    };
}


void variadic_template() {
    print_param_count();
    print_param_count(1);
    print_param_count(1,2);
    print_param_count(1,2,3);
    
    print_params_one('a','b','c','d');
    
    
    print_params_two('x','y','z');
    
    print_params_three('q','w','e','r');
    
    
    vector<int> array{1,2,3,4};
}
