//
//  Ch14Classes.cpp
//  Chapter14
//
//  Created by Juan Ruiz on 11/9/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <iostream>
#include "Ch14Classes.h"

using namespace std;

Numbers::Numbers(int n) {
    // make sure number entered is not negative
    (n>0) ? num = n : num=0;
}

void Numbers::print() const {
    int * array = numArray();
    int size = sizeof(array) / sizeof(int);
    for (int i = 0; i !=size; ++i) {
        cout << array[i] <<  " ";
    }
    cout << endl;
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
    int index = size - 1;
    while (numCpy != 0) {
        // pick of the last number and place it into the end of the array
        array[index] = numCpy%10;
        // remove the digit
        numCpy /= 10;
    }
    
    return array;
}