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

void prob13_1();
void prob13_6();
void prob13_11();

int main(int argc, const char * argv[]) {
    prob13_11();
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
