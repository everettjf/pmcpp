//
//  array.cpp
//  pmcpp-code
//
//  Created by everettjf on 2019/4/25.
//  Copyright © 2019 everettjf. All rights reserved.
//

#include "array_vector.hpp"
#include <array>
#include <algorithm>
#include <vector>

template <typename ARR>
void print_array(ARR arr){
    for(int i=0;i<10;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

template <typename ARR>
void print_array(ARR arr,int size){
    for(int i=0;i<size;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

void array_vector()
{
    int carr[10]; // 内容随机
    print_array(carr);
//
//    int carr1[10] = {1}; // 第一个元素为1，其余0
//    print_array(carr1);
//
//    int carr2[10] = {1,2}; // 第一个元素为1，第二个2，其余0
//    print_array(carr2);



    std::array<int,10> stdarr; // 内容随机
    print_array(stdarr);

    std::array<int,10> stdarr1 = {1}; // 第一个元素为1，其余0
    print_array(stdarr1);
    
    std::array<int,10> stdarr2 = {1,2}; // 第一个元素为1，第二个2，其余0
    print_array(stdarr2);
    
    
    std::array<int, 3> stdarr3 = {1, 2, 3};
    std::sort(stdarr3.begin(), stdarr3.end());
    print_array(stdarr3,3);

    
    // Create a vector containing integers
    std::vector<int> v = {7, 5, 16, 8};
    
    // Add two more integers to vector
    v.push_back(25);
    v.push_back(13);
    print_array(v,v.size());
    
}
