//
//  main.c
//  2.62.c
//
//  Created by Jacob on 10/5/17.
//  Copyright © 2017 Jacob. All rights reserved.
//


int int_shifts_are_arithmetic()
{
    int x = ~0;
    return ((x>>1)==x);
}
