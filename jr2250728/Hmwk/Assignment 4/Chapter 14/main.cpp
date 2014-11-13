//
//  main.cpp
//  Chapter14
//
//  Created by Juan Ruiz on 11/9/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//
//  Chapter 14 problems

#include <iostream>
#include "Ch14Classes.h"

using namespace std;
void prob2();
void prob4();

int main(int argc, const char * argv[]) {
    prob4();
    return 0;
}

void prob2() {
    DayofYear d(96);
    d.print();
}

void prob4() {
    NumDays n1(12);
    --n1;
    NumDays n2(4);
    ++n2;
    cout << n1 + n2 << endl;
}