//
//  main.c
//  2.73.c
//
//  Created by Jacob on 10/5/17.
//  Copyright © 2017 Jacob. All rights reserved.
//
#include <stdio.h>
#include <limits.h>
int saturating_add(int x,int y);

int main(void)
{
    int x = INT_MIN;
    int y = INT_MAX;
    printf("%d",saturating_add(x,y));
    
    return 0;
}


int saturating_add(int x, int y)
{
    int w = sizeof(int)<<3;
    int msbX = -(x>>(w-1));
    int msbY = -(y>>(w-1));
    int sum = x + y;
    int msbSum = -((x+y)>>(w-1));
    int postiveOverflow = ( (!msbX) & (!msbY) & msbSum);
    int negativeOverflow = ( msbX & msbY & (!msbSum));
    return ((-postiveOverflow) & INT_MAX) + ((-negativeOverflow) & INT_MIN) + ((~(-negativeOverflow)) & (~(-postiveOverflow)) & sum);
}
