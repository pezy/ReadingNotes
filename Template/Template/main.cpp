//
//  main.cpp
//  Template
//
//  Created by 陈培哲 on 14-7-9.
//  Copyright (c) 2014年 pezy. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <string>
#include "max.h"

template <typename T>
inline T* const& max(T* const& a, T* const& b) {
    return *a < *b ? b : a;
}

inline char const* const& max(char const* const& a, char const* const& b)
{
    return std::strcmp(a, b) < 0 ? b : a;
}

int main(int argc, const char * argv[])
{
    int i = 42;
    std::cout << "max(7,i) : " << ::max(7, i) << std::endl;
    
    double f1 = 3.4;
    double f2 = -6.7;
    std::cout << "max(f1,f2) : " << ::max(f1, f2) << std::endl;
    
    std::string s1 = "mathematics";
    std::string s2 = "math";
    std::cout << "max(s1,s2) : " << ::max(s1, s2) << std::endl;
    
    int a = 7;
    int b = 42;
    
    std::cout << ::max(a,b) << std::endl;
    
    std::string s = "hey";
    std::string t = "you";
    std::cout << ::max(s, t) << std::endl;
    
    int* p1 = &b;
    int* p2 = &a;
    std::cout << *(::max(p1, p2)) << std::endl;
    
    char const* sz1 = "David";
    char const* sz2 = "Nico";
    std::cout << ::max(sz1, sz2) << std::endl;
    
    return 0;
}

