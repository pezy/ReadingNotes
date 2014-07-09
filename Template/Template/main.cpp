//
//  main.cpp
//  Template
//
//  Created by 陈培哲 on 14-7-9.
//  Copyright (c) 2014年 pezy. All rights reserved.
//

#include <iostream>
#include <string>
#include "max.h"

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
    
    return 0;
}

