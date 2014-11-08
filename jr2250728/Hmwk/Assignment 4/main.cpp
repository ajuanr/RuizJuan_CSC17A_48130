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

int main(int argc, const char * argv[]) {
    prob13_6();
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
