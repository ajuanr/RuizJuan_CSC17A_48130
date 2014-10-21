//
//  main.cpp
//  Midterm
//
//  Created by Juan on 10/18/14.
//  Copyright (c) 2014 Juan. All rights reserved.
//

#include <algorithm> //for sort function
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/*
 * Structures go here
*/
struct Customer {
    int acctNum;     // holds account number
    int balance;      // holds balance at beginning of month
    int chkTotal;     // total of all checks written this month
    int deposits;     // total of all deposits credited this month
};

struct Employee {
    string name;
    int hours;
    int rate;
};

struct statsResult {
    float avg;
    float median;
    int *mode;   //array containing the modes
    int nModes;  //number of modes in the array
    int maxFreq; //max frequency of modes
};

void print(int *array, int size);

/*
 *  Menu and problemlem protoypes
 */
void problem1();
void problem2();
void problem5();

/*
 * Functions for problem 1
 */
void AcctInfo(Customer *);
void newBalance(Customer *);
bool isOvrdrwn(Customer *);

/*
 * Functions for problem 2
 */
int pay(Employee*);
void getEmpInfo(Employee*);
void formatCheck(Employee*, string);

/*
 * Functions for problem 3
 */
statsResult *avgMedMode(int *,int); 

/*
 * Functions for problem 5
 */
template<class T>
T factorial(T);

template<class T>
T maxFac(T);


int main(int argc, const char * argv[]) {
    int a[7] = {3,6,4,3,7,3,9};
    print(a,7);
    avgMedMode(a, 7);
    print(a, 7);
    //problem2();
    return 0;
}

void problem1() {
    Customer *c = new Customer;
    // initialize data members
    c->balance=1000;
    c->chkTotal=0;
    c->deposits=0;
    AcctInfo(c);
    cout << endl;
    newBalance(c);
    cout << "The current balance on account " << c->acctNum
    << " is: " << c->balance << endl;
    if (isOvrdrwn(c)) {
        cout << "Account was over drawn\n"
                "An Overdraft fee of 12 dollars was assesed\n";
        c->balance-=12;
        cout << "The new balance is: " << c->balance << endl;
    }
    cout << endl;
    delete c;
}


void problem2() {
    cout << "How many employees: ";
    int nEmp;
    cin >> nEmp;
    // create array containing employees
    Employee **eArray = new Employee *[nEmp];
    for (int i = 0; i != nEmp; ++i)
        *(eArray+i) = new Employee;
    
    cout << endl;
    
    cout << "Enter the date: ";
    string date;
    cin >> date;
    cout << endl;
    // Get employee info
    for (int i = 0; i != nEmp; ++i) {
        getEmpInfo(*(eArray+i));
        formatCheck(*(eArray + i), date);
        cout << endl;
    }
    
     // deallocate
    for (int i = 0; i != nEmp; ++i) {
        delete *(eArray+i);
    }
    delete []eArray;
    
    
}

void getEmpInfo(Employee *e) {
    cout <<  "Enter the employee name: ";
    cin.ignore();
    getline(cin,e->name);
    cout << "Enter the pay rate: ";
    cin >> e->rate;
    cout << "Enter the hours worked: ";
    cin >> e->hours;
}

int pay(Employee* e) {
    int r0=0;             // total pay
    int r1 = e->rate;     // r1 holds pay rate
    int r2 = e->hours;    // r2 holds hours worked
    int r3;               // temp
    int r4;               // holds the hours > than pay differential

    /// remember r4 must be preserved: push {r4}
    // check if triple time applies
    if ( r2 > 40) {
        r4 = r2 - 40;           // r4 holds hours > 40 worked
        r3 = r1 * 3;            // triple time pay
        r3 = r3 * r4;           // r3 holds that amount of triple time pay
        r2 = r2 - r4;           // move hours into double time
        r0 = r0 + r3;           // add to total pay
    }

    // check if double time applies
    if ( r2 > 20) {
        r4 = r2 - 20;           // r4 holds hours > 20 worked
        r3 = r1 * 2;            // double time pay
        r3 = r3 * r4;           // r3 holds that amount of double time pay
        r2 = r2 - r4;           // move hours into straight time
        r0 = r0 + r3;           // add to total pay
    }

    // check if straight time applies
    if ( r1 > 0) {
        r3 = r1 * r2;
        r0 = r0 + r3;
    }
    return r0;
}

void formatCheck(Employee *e, string date) {
    cout << setw(60) << right << date << endl << endl
    << left << "Pay to the order of: " << e->name
    << setw(35 - (e->name).size()) << right  << "$ " << pay(e) << endl;
    
    cout << endl;
}

void problem5() {
    unsigned uB;
    cout << "Largest unsigned byte factorial is: " << maxFac(uB) << endl;
    signed sB;
    cout << "Largest signed byte factorial is: " << maxFac(sB) << endl;
    unsigned short uS;
    cout << "Largest unsigned short factorial is: " << maxFac(uS) << endl;
    signed short sS;
    cout << "Largest signed short factorial is: " << maxFac(sS) << endl;
    unsigned int uI;
    cout << "Largest unsigned int factorial is: " << maxFac(uI) << endl;
    signed int sI;
    cout << "Largest signed int factorial is: " << maxFac(sI) << endl;
    float fl;
    cout << "Largest float factorial is: " << maxFac(fl) << endl;
    
}


// Function calculates factorials
template<class T>
T factorial(T n) {
    if (n==0)
        return 1;
    return n*factorial(n-1);
}

template<class T>
T maxFac(T) {
    T n=2; // can't use 1, factorial(1) == factorial(0)
    while (factorial(n-1) < factorial(n)) {
        ++n;
    }
    // current n overflows go back one
    return --n;
}

void AcctInfo(Customer *c) {
    bool valid = false;
    do {
        cout << "Enter the account number: ";
        cin >> c->acctNum;
        // if account number is more than 5 digits
        // this result will be >= to 1
        if (c->acctNum / 100000 < 1)
            valid=true;
    } while (!valid);
    
    cout << "Enter the current balance: ";
    cin >> c->balance;
    
    cout << endl;
    
    cout << "Were any checks written this month. 'y' for yes: ";
    char response;
    cin >> response;
    if (response == 'y') {
        int amnt;
        do {
            cout << "Enter the amount of the check. -1 to quit: ";
            cin >> amnt;
            c->chkTotal +=amnt;
        } while(amnt>0);
    }
    cout << endl;
    cout << "Were any deposits made this month. 'y' for yes: ";
    cin >> response;
    if (response == 'y') {
        int amnt;
        do {
            cout << "Enter the amount of the deposit. -1 to quit: ";
            cin >> amnt;
            c->deposits += amnt;
        } while(amnt>0);
    }
}

void newBalance(Customer *c) {
    c->balance -= c->chkTotal;
    c->balance += c->deposits;
}
bool isOvrdrwn(Customer *c) {
    return (c->balance < 0) ? true: false;
}

statsResult *avgMedMode(int *array, int size) {
    sort(array, array+size);
}


void print(int *array, int size) {
    for (int i = 0; i != size; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
}