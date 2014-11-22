//
//  main.cpp
//  Chapter 15
//
//  Created by Juan Ruiz on 11/21/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <iostream>
#include <string>
#include "Chapter15.h"

using namespace std;

void problem1();
void problem2();

int main(int argc, const char * argv[]) {
    problem2();
    return 0;
}

void problem1() {
    cout << "In problem problem 1 - Chapter 15 Problem 1\n";
    string name, num, hDate;
    
    cout << "Enter the employee name, number, and hire date:\n";
    cin >> name >> num >> hDate;
    cout << "Is this an:\n"
            "1. Employee\n"
            "2. Production Worker\n";
    int empType;
    cin >> empType;
    if ( empType == 2) {
        int shift;
        float pay;
        cout << "Enter the employee shift(1. Day, 2. Night)\n"
                "and the employee pay rate:\n";
        cin >> shift >> pay;
        Employee *worker =
            new ProductionWorker(name, num, hDate, shift, pay);
        worker->print();
        
        delete worker;
    }
    else {
    Employee *emp = new Employee(name, num, hDate);
    emp->print();
    delete emp;
    }
    cout << endl;
}

void problem2() {
    FileFilter *file = new Encryption(5);
    char inName[20] = "test.txt";
    ifstream inFile(inName, ios::in);
    char outName[20] = "out.txt";
    ofstream outFile(outName, ios::out);
    file->doFilter(inFile, outFile);
}