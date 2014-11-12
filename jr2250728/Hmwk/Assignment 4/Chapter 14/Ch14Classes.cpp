//
//  Ch14Classes.cpp
//  Chapter14
//
//  Created by Juan Ruiz on 11/9/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include "Ch14Classes.h"

Numbers::Numbers(int n) {
    // make sure number entered is not negative
    (n>0) ? num = n : num=0;
}

void Numbers::print() const {
    
}

int* Numbers::numArray() const{
    int size = 0;
    int numCpy = num;
    while ( numCpy != 0 ) {
        numCpy/=10;
        size++;
    }
    // reset the copy of num to store the values in an array
    numCpy = num;
    int* array = new int[size];
    
    // pick of the values and place them into the array
    // starting at the end of the array
    while (numCpy != 0) {
        // pick of the last number and place it into the end of the array
        
    }
    
    
    return array;
}