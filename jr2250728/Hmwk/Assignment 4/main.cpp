//
//  main.cpp
//  RuizJuan-Chapter13
//
//  Created by Juan Ruiz on 11/7/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Ch13Prototypes.h"

using namespace std;

void prob13_1();
void prob13_6();
void prob13_11();
void prob13_12();

int main(int argc, const char * argv[]) {
    srand(static_cast<unsigned int>(time(0)));
    prob13_12();
    return 0;
}

void prob13_1() {
    Date d(02, 23, 2014);
    cout << "Print date in what format:\n"
            "1. mm/dd/yyyy\n"
            "2. month dd, yyyy\n"
            "3. dd month yyyy\n";
    int choice;
    cin >> choice;
    d.print(choice);
}

void prob13_6() {
    cout << "Enter the item number: ";
    int itemNum;
    cin >> itemNum;
    cout << "Enter the item quantity: ";
    int quantity;
    cin >> quantity;
    cout << "Enter the item cost: ";
    float cost;
    cin >> cost;
    
    Inventory item(itemNum, cost, quantity);
    cout << "The total cost for item: " << item.getItemNumber() << " is: $"
    << item.getTotalCost() << endl;
}

void prob13_11() {
    cout << "Enter the size of the array: ";
    int n;
    cin >> n;
    Numbers numArray(n);
    // print the array elements using the get member function
    for (int i = 0; i != n; ++i) {
        if (i %10 == 0) cout << endl;
        cout << numArray.getNum(i) << " ";
    }
    cout << endl;
    cout << "The largest value is: " << numArray.max() << endl;
    cout << "The smallest value is: " << numArray.min() << endl;
    cout << "The average value is: " << numArray.avg() << endl;
}

void prob13_12() {
    // problem ho
    const int size = 7;
    Payroll *emp = new Payroll[7];
    // fill the array with randomly generated employee pay and hours
    for (int i = 0; i != size; ++i) {
        // create random hour between 0 and 60
        int randHr = rand() % 59 + 1;
        // create random payRate between 1 and 45
        int randRate = rand() % 45 + 1;
        emp[i].setHours(randHr);
        emp[i].setRate(randRate);
    }
    
    // print the employee pay
    for (int i = 0; i != size; ++i) {
        cout << "Pay for employee" << i+1 << ":\n\t"
             << emp[i].getHours() << " hours x "
             << emp[i].getRate() << " = $" << emp[i].pay()
             << endl;
    }
    
    // deallocate
    delete []emp;
}