/* 
 * Ruiz, Juan - Assignment 3 - 48130
 * 5 problems from chapter 10
 * 5 problems from chapter 12
 * 
 */

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

void problem10_12();
bool isValid(string);

/*
 * 
 */
int main(int argc, char** argv) {

    return 0;
}

/*
* The password should be at least six characters long.
* The password should contain at least one uppercase and
* at least one lowercase letter.
* The password should have at least one digit.
 */
void problem10_12() {
    string pswd;
    do {
    cout << "Enter password\n"
            "Password should be at least six characters long.\n"
            "The password should contain at least one uppercase and
            " at least one lowercase letter.\n"
            "The password should have at least one digit.\n";
    cin >> pswd;
    } while (!isValid(pswd));
}

bool isValid(string pswd) {
    bool length = false;    // password must be six digits
    bool upper = false;    // contain at least one uppercase character
    bool lower = false;    // contain at least one lowercase character
    bool digit = false;    // contain at least one digit
    
    
}