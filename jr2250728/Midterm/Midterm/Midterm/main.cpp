//
//  main.cpp
//  Midterm
//
//  Created by Juan on 10/18/14.
//  Copyright (c) 2014 Juan. All rights reserved.
//

#include <iostream>
#include <string>

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


/*
 *  Menu and problemlem protoypes
 */

void problem1();
void problem5();



/*
 * Functions for problem 1
 */
template<class T>
T factorial(T);

template<class T>
T maxFac(T);


/*
 * Functions for problem 2
 */
void AcctInfo(Customer *);
void read(Customer *, int);


int main(int argc, const char * argv[]) {
    //problem5();
    return 0;
}

void problem1() {
    cout << "You called problem 1\n";
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
    
    int n;
    do {
        cout << "Enter"
    }
}


// function reads in checks or deposits depending on type
// type should be 1 or -1
// if -1, then a check was written and it will be subtracted from balance
// otherwise add to balance
void read(Customer *c, int type ) {
    int num;
    c->balance += (num * type);
}
