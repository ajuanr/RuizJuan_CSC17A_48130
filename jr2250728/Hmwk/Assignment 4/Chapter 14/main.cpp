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
#include <ctime>
#include <string>
#include <iomanip>
#include "Ch14Classes.h"

using namespace std;

void Menu();
int getN();
void def(int);
void prob2();
void prob4();
void prob10();
void prob13();
void prob15();

int main(int argc, const char * argv[]) {
    srand(static_cast<unsigned int>(time(0)));
    int inN;
    do{
        Menu();
        inN=getN();
        switch(inN){
            case 1:    prob2();cout << endl;break;
            case 2:    prob4();cout << endl;break;
            case 3:    prob10();cout << endl;break;
            case 4:    prob13();cout << endl;break;
            case 5:    prob15();cout << endl;break;
            default:   def(inN);
        }
    } while(inN<6);
    return 0;
}

void Menu()
{
    cout<<"Type 1 for problem 2"<<endl;
    cout<<"Type 2 for problem 4"<<endl;
    cout<<"Type 3 for problem 10"<<endl;
    cout<<"Type 4 for problem 13"<<endl;
    cout<<"Type 5 for problem 15"<<endl;
    cout<<"Type 6 to exit \n"<<endl;
}
int getN()
{
    int inN;
    cin>>inN;
    return inN;
}

void def(int inN)
{
    cout<<"You typed "<<inN<<" to exit the program"<<endl;
}

void prob2() {
    cout << "In problem 2\n";
    cout << "Enter a number from 1 to 365: ";
    int day;
    cin >> day;
    DayofYear d(day);
    d.print();
}

void prob4() {
    cout << "In problem 4\n8 hours = 1 workday\n";
    cout << "Enter the number of hours worked for day 1: ";
    int hours;
    cin >> hours;
    NumDays n1(hours);
    cout << hours << " hours = " << n1.getDays() << " workdays" << endl;
    cout << "Enter the number of hours worked for day 2: ";
    cin >> hours;
    NumDays n2(hours);
    n1 = n1 + n2;
    cout << "Total number of workdays is: " << n1.getDays() << endl;
}

void prob10() {
    cout << "In problem 10\n";
    // create an array of four DivSales objects
    // each representing a geographic region
    const int nRegion = 4;      // number of regions
    DivSales array[nRegion];
    for (int i = 0; i != nRegion; ++i) {
        int q1 = rand() % 20000;
        int q2 = rand() % 20000;
        int q3 = rand() % 20000;
        int q4 = rand() % 20000;
        // fill each quarter with the generated sales amounts
        array[i].setSales(q1, q2, q3, q4);
    }
    // print out the sales report
    string border = string(29, '-');
    cout << border << endl;
    for (int i=0; i != nRegion; ++i) {
        array[i].print();
        cout << border << endl;
    }

    cout << "Total yearly sales for all divisions: $";
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
    cout << "Car get 24 miles/gallon\n";
    cout << "Initial mileage on car: " << car.getMileage() << endl;
    cout << "Initial amount of gas in car: " << tank.getGallons() << endl;
    cout << endl;
    
    // drive until gas tank is empty
    for (int i = 0; tank.getGallons() != 0; ++i) {
        ++car; // every iteration is one mile traveled
        if (( i+1) % 24 == 0 ) {
            cout << "Miles traveled: " << car.getMileage() - 1000 << endl;
            --tank;
            cout << "Gas left in tank: " << tank.getGallons() << " gallons\n\n";
        }
    }
    cout << "Final mileage on car: " << car.getMileage() << " miles\n";
}