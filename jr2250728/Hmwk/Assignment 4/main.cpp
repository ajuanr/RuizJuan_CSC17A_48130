//
//  main.cpp
//  RuizJuan-Chapter13
//
//  Created by Juan Ruiz on 11/7/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <iostream>
#include "Ch13Prototypes.h"

using namespace std;

int main(int argc, const char * argv[]) {

    return 0;
}

void problem13_1() {
    Date d(02, 23, 2014);
    cout << "Print date in what format:\n"
            "1. mm/dd/yyyy\n"
            "2. month dd, yyyy"
            "3. dd month yyyy";
    int choice;
    cin >> choice;
    d.print(choice);
}
