//
//  main.c
//  2.73-redo.c
//
//  Created by Jacob on 10/6/17.
//  Copyright © 2017 Jacob. All rights reserved.
//
#include <stdio.h>
#include <limits.h>
int saturating_add(int x,int y)
{
    int w = sizeof(int)<<3;
    int msbX = -(x>>(w-1));
    int msbY = -(y>>(w-1));
    int sum = x + y;
    int overflow = __builtin_add_overflow_p(x,y,(int)0);
    int positiveOverflow = overflow && !msbX;
    int negativeOverflow = overflow && msbX;
    return ((-positiveOverflow) & INT_MAX) + ((-negativeOverflow) & INT_MIN) + ((~(-negativeOverflow)) & (~(-positiveOverflow)) & sum);
}

int main(){}
