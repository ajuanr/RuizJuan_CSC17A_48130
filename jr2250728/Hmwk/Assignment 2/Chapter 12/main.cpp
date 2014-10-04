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

struct Company {
    string division;  // East, North, West or South
    int quarter;      // 1,2,3, or 4
    float sales;      // Quarterly sales
};

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

// Outputs the first 10 lines of a file
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

// adds line numbers to the beginning of every line
// in a file
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
        cout << "The last 10 lines are:\n";
        int nLines =0; // total lines
        char c;
        file.get(c);
        // find total number of lines
        while (!file.eof() && nLines != 10) {
            if (c == '\n') ++nLines;
            file.get(c);

        }
        cout << "Num lines " << nLines;
        // clear eof flag
        file.clear();
        file.seekg(ios::beg);
        
        int current=0;
        file.get(c);
        while (!file.eof()) {
            if (c == '\n') ++current;
            cout << current << endl;
            if (current > nLines-10) {
                cout << c;
            }
            file.get(c);
                
                
        }
    }
    else
        cout << "File failed to open\n";
        
}

// simple encryption
// adds 10 to every character in a file
// writes to a second file
void prob12_9() {
    char ifName[20];
    cout << "Enter the name of the file you want encrypted: ";
    cin >>ifName;
    fstream in(ifName, ios::in);
    if (in) {
        cout << "Enter the name of the new encrypted file: ";
        char ofName[20];
        cin >> ofName;
        fstream out(ofName, ios::out);
        
        char c;
        in.get(c);
        while (!in.eof()) {
            c+=10;
            out << c;
            in.get(c);
        }
    }
    else
        cout << ifName <<  " failed to open\n";
}


void prob12_11() {
    Company *c = new Company;
    cout << "Enter your division(North, South, East, or West): ";
    cin >> c->division;
    
    cout << "Enter the quarter(1, 2, 3, or 4): ";
    cin >> c->quarter;
    
    // sales can't be negative
    do {
        cout << "Enter the quarterly sales: ";
        cin >> c->sales;
    } while (c->sales < 0);
    
    cout << "Report will be written to: " << c->division << ".txt";
    
    string fName = c->division + ".txt";
    
    fstream out(fName.c_str(), ios::out);
    out << "Division: " << c->division << endl
        << "Quarter: " << c->quarter << endl
        << "Quarterly Sales: " << c->sales << endl;
    
    cout << endl;
    delete c;
}