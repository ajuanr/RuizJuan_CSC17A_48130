//
//  main.cpp
//  Chapter14
//
//  Created by Juan Ruiz on 11/9/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//
//  Chapter 14 problems

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include "Ch14Classes.h"

using namespace std;
void prob2();
void prob4();
void prob10();
void prob13();
void prob15();

int main(int argc, const char * argv[]) {
    prob15();
    return 0;
}

void prob2() {
    cout << "In problem 2" << endl;
    DayofYear d(96);
    d.print();
}

void prob4() {
    cout << "In problem 4" << endl;
    NumDays n1(12);
    --n1;
    NumDays n2(4);
    ++n2;
    cout << n1 + n2 << endl;
}

void prob10() {
    cout << "In problem 10" << endl;
    // create an array of four DivSales objects
    // each representing a geographic region
    const int nRegion = 4;
    DivSales array[nRegion];
    for (int i = 0; i != nRegion; ++i) {
        int q1 = rand() % 20000;
        int q2 = rand() % 20000;
        int q3 = rand() % 20000;
        int q4 = rand() % 20000;
        
        array[i].setSales(q1, q2, q3, q4);
    }
    string border = string(24, '-');
    cout << border << endl;
    for (int i; i != nRegion; ++i) {
        cout << "Sales for Region " << i+1 << endl;
        for (int j = 0; j != 4; ++j) {
            cout << "|" << array[i].getDivSales(j);
        }
        cout << "|";
        cout << endl << border << endl;
    }
    cout << "Total yearly sales for all divisions: ";
    cout << DivSales::yrlySales << endl;
}

void prob13() {
    cout << "In problem 13\n";
    
    RoomCarpet room;
    cout << "The total cost for carpeting is: $";
    cout << room.totalCost() << endl;
}

void prob15() {
    cout << "In problem 15\n";
    
    // create a car with 0 miles traveled and a full tank of gas
    Odometer car(1000);
    FuelGauge tank(15);
    cout << "Initial mileage on car: " << car.getMileage() << endl;
    cout << "Initial amount of gas in car: " << tank.getGallons() << endl;
    cout << endl;
    
    // drive until gas tank is empty
    for (int i = 0; tank.getGallons() != 0; ++i) {
        ++car; // every iteration is one mile traveled
        if (( i+1) % 24 == 0 ) {
            cout << "Miles traveled: " << car.getMileage() - 1000 << endl;
            --tank;
            cout << "Gas left in tank: " << tank.getGallons() << "gallons\n\n";
        }
    }
    cout << "Final mileage on car: " << car.getMileage() << " miles\n";
}