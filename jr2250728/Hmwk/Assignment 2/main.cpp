/* 
 * Ruiz, Juan - Assignment 3 - 48130
 * Using 6th edition of the textbook
 * 5 problems from chapter 10
 * 5 problems from chapter 12
 * 
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void prob10_10();
void prob10_12();
void prob10_19();
bool isValid(string);
void formatCheck(string, string, float);
string numToStr(float);

string edit(string, string, string);

/*
 * 
 */
int main(int argc, char** argv) {
    //prob10_12();
    prob10_19();
    //prob10_10();
    return 0;
}

/*
 * User enters a string
 * Function replaces occurrences of a string
 * with another string
 */

void prob10_10() {
    string str1;
    cout << "Enter a sentence:";
    getline(cin, str1);
    
    string str2;
    cout << "Enter the word you want replaced: ";
    cin >> str2;
    
    string str3;
    cout << "Replacement word: ";
    cin >> str3;
    
    string newStr = edit(str1, str2, str3);
    cout << newStr << endl;
}

/*
* The password should be at least six characters long.
* The password should contain at least one uppercase and
* at least one lowercase letter.
* The password should have at least one digit.
 */
void prob10_12() {
    string pswd;
    do {
    cout << "Enter password\n"
            "Password should be at least six characters long.\n"
            "The password should contain at least one uppercase and"
            " at least one lowercase letter.\n"
            "The password should have at least one digit.\n";
    cin >> pswd;
    } while (!isValid(pswd));
    cout << "\nSuccess!\n";
}

/*
 * Creates a simulated check
 * users enter the date, the name on the check and the amount
 */
void prob10_19() {
    string date;
    cout << "Enter the date: ";
    cin >> date;
    
    string name;
    cout << "Enter name on the check: ";
    cin.ignore();
    getline(cin, name);
    
    float amnt;
    do {
    cout << "Enter the amount, no more than $10,000: ";
    cin >> amnt;
    } while (amnt < 0  || amnt > 10000); // amount cannot be negative
    cout << endl;
    
    formatCheck(date, name, amnt);
}

// used for problem 10.12
// check whether the entered password is valid
bool isValid(string pswd) {
    bool length = false;    // password must be six digits
    bool upper = false;    // contain at least one uppercase character
    bool lower = false;    // contain at least one lowercase character
    bool digit = false;    // contain at least one digit
    
    // first check for appropriate length
    if (pswd.length() < 6) return false;
    
    for (string::const_iterator iter = pswd.begin(); iter != pswd.end();
            ++iter) {
        if (islower(*iter)) lower = true;
        if (isupper(*iter)) upper = true;
        if (isdigit(*iter)) digit = true;
        
        // all conditions have been met. Stop looping and exit
        if (lower && upper && digit) return true;
    }
    
    return false;
}

void formatCheck(string date, string name, float amnt) {
    string amntTxt = numToStr(amnt);
    cout << setw(60) << right << date << endl << endl
         << left << "Pay to the order of: " << name << '\t' << amnt << endl
         << amntTxt;
}

string numToStr(float amnt) {
    
    // get how many cents are in the amount
    int cents = static_cast<int>(amnt * 100) % 100 + 1;

    // max value is $10000 not including decimal
    // max size is 5
    const int MAX = 5;
    // create array to hold the individual digits. set all indexes to zero
    int array[MAX]= {0};
    
    // int copy of float amnt
    int amntCpy = static_cast<int>(amnt);
    // pick off the individual digits in the amount
    // go to -1 to make sure to include most significant digit in amnt in array
    for (int i = MAX-1; i!= -1; --i) {
        array[i] = amntCpy %10;
        amntCpy/= 10;
    }

    for (int i = 0; i != MAX; ++i)
        cout << array[i];
    cout << endl;
    
    // e.g 90 -> "ninety"
    char * tens[8] = {"twenty", "thirty", "forty", "fifty", "sixty",
                  "seventy", "eighty", "ninety"};
    
    // e.g 4 -> "four"
    char *ones[9] = {"one", "two", "three", 
                      "four", "five", "six",
                      "seven", "eight", "nine"};
    
    string text;
    for (int i = 0; i != MAX; ++i) {
        // ten thousands place
        if (array[i] && i == 0) {
            text += "Ten Thousand";
        }
        // thousands place
        if (array[i] && i==1){
            text += ones[array[i]-1];
            text += " thousand";
        }
        // hundreds place
        if (array[i] && i==2) {
            text += ones[array[i]-1];
            text += " hundred";
        }
    
    }
    
    return text;
}

// edit the string from problem 10.10
// replaces string s2 in string s1 with  string s3
string edit(string s1, string s2, string s3) {
    string s1Cpy = s1;
    
    size_t iter = 0;
    size_t end = s1.length();
    while (iter != end) {
            iter = s1.find(s2);
            s1.erase(iter, iter + s2.length());
            s1.insert(iter, s3);
    }
    
    return s1Cpy;
}