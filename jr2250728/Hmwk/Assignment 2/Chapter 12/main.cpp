/* 
 * Ruiz, Juan - Assignment 3 - 48130
 * Using 6th edition of the textbook
 * 5 problems from chapter 10
 * 
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void Menu();
int getN();
void def(int);
void prob12_1();
void prob12_5();
void prob12_6();
void prob12_9();
void prob12_11();

/*
 * 
 */
int main(int argc, char** argv) {
    int inN;
    do{
        Menu();
        inN=getN();
        switch(inN){
            case 1:    prob12_1();cout << endl;break;
            case 2:    prob12_5();cout << endl;break;
            case 3:    prob12_6();cout << endl;break;
            case 4:    prob12_9();cout << endl;break;
            case 5:    prob12_11();cout << endl;break;
            default:   def(inN);
        }
    } while(inN<6);
    
    return 0;
}

void Menu()
{
    cout<<"Type 1 for problem 1"<<endl;
    cout<<"Type 2 for problem 2"<<endl;
    cout<<"Type 3 for problem 3"<<endl;
    cout<<"Type 4 for problem 4"<<endl;
    cout<<"Type 5 for problem 5"<<endl;
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

void prob12_1() {
    char fName[20];
    cout << "Enter the file name: ";
    cin >> fName;
    fstream file(fName, ios::in);
    if(file) {
        cout << "The first 10 lines are:\n";
        int line =0;
        char c;
        file.get(c);
        while (!file.eof() && line != 10) {
            if (c == '\n') ++line;
            cout << c;
            file.get(c);
        }
    }
    else
        cout << "File failed to open.\n";
}
void prob12_5() {
    char fName[20];
    cout << "Enter the file name: ";
    cin >> fName;
    fstream file(fName, ios::in);
    if(file) {
        int line =1;
        cout << line << ": ";
        char c;
        file.get(c);
        while (!file.eof()) {
            if (c == '\n'){
                ++line;
                cout << c << line << ": ";
            }
            else
                cout << c;
            file.get(c);
        }
    }
    else
        cout << "File failed to open.\n";
}
void prob12_6() {
    char fName[20];
    cout << "Enter the file name: ";
    cin >> fName;
    fstream file(fName, ios::in);
    if(file) {
        cout << "Enter a word to search for: ";
        string search;
        cin >> search;
        string current;
        int line = 1;
        while(file >> current) {
            if (current == "\n")
                ++line;
            //cout << search << " " << current;
            if (search.compare(current)==0) {
                cout << search << "appeared on line: " << line;
            }
        }
    }
    else
        cout << "File failed to open.\n";
}
void prob12_9() {
    cout << "This is problem 4" << endl;
}
void prob12_11() {
    cout << "This is problem 5" << endl;
}