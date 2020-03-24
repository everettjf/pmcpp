//
//  main.cpp
//  cpp-signature
//
//  Created by everettjf on 2020/3/22.
//  Copyright © 2020 everettjf. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef double          f64;
typedef float           f32;
typedef uint64_t        u64;
typedef int64_t         i64;
typedef uint32_t        u32;
typedef int32_t         i32;
typedef uint16_t        u16;
typedef int16_t         i16;
typedef uint8_t         u8;
typedef int8_t          i8;

template<char c>
struct m3_sig {
    static const char value = c;
};

template<typename T> struct m3_type_to_sig;
template<> struct m3_type_to_sig<i32> : m3_sig<'i'> {};
template<> struct m3_type_to_sig<i64> : m3_sig<'I'> {};
template<> struct m3_type_to_sig<f32> : m3_sig<'f'> {};
template<> struct m3_type_to_sig<f64> : m3_sig<'F'> {};
template<> struct m3_type_to_sig<void> : m3_sig<'v'> {};
template<> struct m3_type_to_sig<void *> : m3_sig<'*'> {};
template<> struct m3_type_to_sig<const void *> : m3_sig<'*'> {};

template <typename Ret, typename ... Args>
string GetTypeEncoding() {
    char arr[] = {
        m3_type_to_sig<Ret>::value,
        '(',
        m3_type_to_sig<Args>::value...,
        ')',
        0
    };
    return string(arr);
}

template <auto value>
class FunctionWrapper;

template<typename Ret, typename ... Args, Ret (*Fn)(Args...)>
class FunctionWrapper<Fn> {
public:
    static string GetFunctionSignature() {
        return GetTypeEncoding<Ret, Args...>();
    }
};



i32 foo1(i32 a, i32 b) {
    return 0;
}

i64 foo2(i64 a, i64 b) {
    return 0;
}


int main(int argc, const char * argv[]) {
    

    cout << m3_type_to_sig<i32>::value << endl;
    
    cout << GetTypeEncoding<i32,i32,i32>() << endl;
    cout << GetTypeEncoding<i32,f32,f32>() << endl;
    cout << GetTypeEncoding<i64,i64>() << endl;
    
    cout << FunctionWrapper<foo1>::GetFunctionSignature() << endl;
    cout << FunctionWrapper<foo2>::GetFunctionSignature() << endl;



    return 0;
}
