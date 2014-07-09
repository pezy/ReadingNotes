//
//  max2.h
//  Template
//
//  Created by 陈培哲 on 14-7-9.
//  Copyright (c) 2014年 pezy. All rights reserved.
//

#ifndef __Template__max2__
#define __Template__max2__

#include <iostream>

inline int const& max (int const& a, int const& b)
{
    return a < b ? b : a;
}

template <typename T>
inline T const& max (T const& a, T const& b)
{
    return a < b ? b : a;
}

template <typename T>
inline T const& max(T const& a, T const& b, T const& c) {
    return ::max(::max(a,b), c);
}


#endif /* defined(__Template__max2__) */
