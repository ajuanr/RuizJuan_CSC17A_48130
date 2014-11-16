//
//  main.cpp
//  Ruiz, Juan - Chapter 13 Problems
//
//  Files required:
//      Ch13Prototypes.h
//      Ch13Defs.cpp
//
//  Created by Juan Ruiz on 11/7/14.
//
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Ch13Prototypes.h"

using namespace std;

void Menu();
int getN();
void def(int);
void prob13_1();
void prob13_6();
void prob13_11();
void prob13_12();
void prob13_15();

int main(int argc, const char * argv[]) {
    //srand(static_cast<unsigned int>(time(0)));
    int inN;
    do{
        Menu();
        inN=getN();
        switch(inN){
            case 1:    prob13_1();cout << endl;break;
            case 2:    prob13_6();cout << endl;break;
            case 3:    prob13_11();cout << endl;break;
            case 4:    prob13_12();cout << endl;break;
            case 5:    prob13_15();cout << endl;break;
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
    
    InventoryItem item(itemNum, cost, quantity);
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
    // problem wants array of seven employees
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

void prob13_15() {
    CashRegister cr;
    cr.buyItem();
    //cr.print();
}