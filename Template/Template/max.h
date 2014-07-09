//
//  max.h
//  Template
//
//  Created by 陈培哲 on 14-7-9.
//  Copyright (c) 2014年 pezy. All rights reserved.
//

#ifndef Template_max_h
#define Template_max_h

template <typename T>
inline T const& max (T const& a, T const& b)
{
    return a < b ? b : a;
}


#endif
