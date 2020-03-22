//
//  forwarding_reference.cpp
//  pmcpp-code
//
//  Created by everettjf on 2019/4/19.
//  Copyright © 2019 everettjf. All rights reserved.
//

#include "forwarding_reference.hpp"
#include <type_traits>
#include <iostream>

using namespace std;


template <typename T, typename... Args>
void bar(Args&&... args) {
    
}


template <typename T, typename... Args>
void foo(Args&&... args) {
    bar(std::forward<Args>(args)...);
}


void g(int& param) {
    cout<< "g int&"<<endl;
}

void g(int&& param) {
    cout << "g int&&" <<endl;
}

template <typename T>
void f(T&& param){
    g(std::forward<T>(param));
}

int call(){
    return 1;
}
void forwarding_reference(){
    f(1);
    
    int a = 1;
    f(a);
    
    f(call());
}

