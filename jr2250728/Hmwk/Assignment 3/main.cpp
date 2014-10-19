/*
*    Ruiz, Juan - Assignment 3 - 48130
*/
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Movie {
    string title;
    string director;
    string released;
    string length; // the running time
};

struct Weather {
    int total;          // total rainfall
    int high;         // high temp
    int low;          // low temp
};

struct Company {
    string division;  // East, North, West or South
    int qrtrSale[4];      // 1,2,3, or 4
    float sales;      // Total sales
};


struct MonthlyBudget {
    static const int size = 10;
    const char *expense[size] = {"Housing", "Utilities", "Household Expenses",
                        "Transportation", "Food", "Medical", "Insurance",
                        "Entertainment", "Clothing", "Miscellanous"};
    // these values represent the default budget
    float budget[size]= {500.00, 150.00, 65.00, 50.00, 250.00,
                       30.00, 100.00, 150.00, 75.00, 50.00};
};

struct Course {
    string name;                // Student name
    string idNum;               // Student id num
    int *tests;                 // Holds test resuls
    float avg;                  // Average grade
    char grade;                 // letter grade
    
};
/*
 * Problem Prototypes begin here
 */
void Menu();
int getN();
void def(int);
void prob11_1();
void prob11_3();
void prob11_4();
void prob11_11();
void prob11_12();

/*
 * Utility functions for assigned problems
 */
void prntMov(const Movie&);
void rdWthr(Weather *, int =12); // 12 months in a year
void calcWthr(Weather *, int = 12);
void spent(MonthlyBudget *);
void cmpBudg(MonthlyBudget *, MonthlyBudget *);
char ltrGrade(int);
Course* getCourse();

int main() {
    int inN;
    do{
        Menu();
        inN=getN();
        switch(inN){
            case 1:    prob11_1();cout << endl;break;
            case 2:    prob11_3();cout << endl;break;
            case 3:    prob11_4();cout << endl;break;
            case 4:    prob11_11();cout << endl;break;
            case 5:    prob11_12();cout << endl;break;
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

// Create a structure holding movie data
// Create two movies
// Print the movie data
 void prob11_1() {
    Movie m1, m2;
    m1.title = "Gladiator";
    m1.director = "Ridley Scott";
    m1.released = "2000";
    m1.length = "155 min.";
    
    m2.title = "The Good, the Bad and the Ugly";
    m2.director = "Sergio Leone";
    m2.released = "1966";
    m2.length = "161 min";
    
    prntMov(m1);
    cout << endl;
    prntMov(m2);
    
}
 
 void prntMov(const Movie &m) {
     cout << setw(14) << left << "Title: " << m.title << endl
          << setw(14) << left  << "Director: " << m.director << endl
          << "Release Date: " << m.released << endl
          << "Running Time: " << m.length << endl;
     
 }

void prob11_3() {
    Company *comp = new Company;
    cout << "Enter company division (East, South, West or North): ";
    cin >> comp->division;
    float totalSale=0;
    for (int i = 0; i != 4; ++i) {
        cout << "Enter the quarterly sales for quarter " << i+1 << ": ";
        cin >> *(comp->qrtrSale+i);
        totalSale+=*(comp->qrtrSale+i);;
        
    }
    cout << endl;
    cout << "Info for division: " << comp->division << endl;
    cout << "Total sales were: " << totalSale << endl;
    cout << "Average quarterly sales were: " << totalSale / 4 << endl;
    
    delete comp;
}
 
 void prob11_4() {
     Weather data[12];          // array containing weather data for the year
     rdWthr(data);
     calcWthr(data);
     return;
 }
 
 void prob11_11() {
    MonthlyBudget *mb= new MonthlyBudget;
    MonthlyBudget *actual = new MonthlyBudget;
    
    spent(actual);
    cmpBudg(mb, actual);
    
    delete actual;
    delete mb;
    
 }

void prob11_12() {
    cout << "How many students are there: ";
    int nStudent;
    cin >> nStudent;
    Course *roster = new Course[nStudent];
    cout << "How many tests were taken: ";
    int nTests;
    cin >> nTests;
    for (int i = 0; i != nStudent; ++i) {
        roster[i].tests = new int[nTests];
    }

    for (int i = 0; i != nStudent; ++i) {
        cout << "Enter the student name: ";
        cin >> roster[i].name;
        cout << "Enter the student id: ";
        cin >> roster[i].idNum;
        for (int j = 0; j != nTests; ++j) {
            cout << "Enter score for test " << j+1 << ": ";
            cin >> roster[i].tests[j];
        }
        cout << endl;
    }
    
    // calculate the average grade
    for (int i = 0; i != nStudent; ++i) {
        int total = 0;
        for (int j = 0; j != nTests; ++j) {
            total += roster[i].tests[j];
        }
        roster[i].avg = total/nTests;
    }
    // get letter grade
    for (int i = 0; i != nStudent; ++i)
        for (int j = 0; j != nTests; ++j)
            roster[i].grade=ltrGrade(roster[i].avg);
    
    // Print students
    for (int i = 0; i != nStudent; ++i) {
            cout << "Name: " << roster[i].name << endl;
            cout << "Student id: " <<roster[i].idNum << endl;
            cout << "Test average: " << roster[i].avg << endl;
            cout << "Letter Grade: " << roster[i].grade << endl;
        cout << endl;
    }
    
    // deallocate
    for (int i = 0; i != nStudent; ++i)
        delete [] roster[i].tests;
    delete []roster;
}

char ltrGrade(int c) {
    if ( c > 90 )
        return 'A';
    else if ( c > 80)
        return 'B';
    else if (c > 70)
        return 'C';
    else if (c > 60)
        return 'D';
    else
        return 'F';
}

 void rdWthr(Weather* w, int size) {
     const char *months[12] = {"January", "February", "March", "April",
                           "May", "June", "July", "August",
                           "September", "October", "November", "December"};
     
     for (int i = 0; i != size; ++i) {
         cout << "Data for " << months[i] << ":\n";
         cout << "Enter total rainfall: ";
         cin >> w[i].total;
         cout << "Enter the high temperature: ";
         cin >> w[i].high;
         cout << "Enter the low temperature: ";
         cin >> w[i].low;
         cout << endl;
     }
     cout << endl;
     
 }

// Calculate weather data
 void calcWthr(Weather *w, int size) {
     const char *months[12] = {"January", "February", "March", "April",
                           "May", "June", "July", "August",
                           "September", "October", "November", "December"};
     int ttl_rain=0;                  // total rainfall
     int high=-100, low = 140;        // high and lowtemperatures
     int index_h=0, index_l=0;          // when high and low temps occured;
     
     for (int i = 0; i != size; ++i) {
         ttl_rain+=w[i].total; // add monthly rainfall to total rainfall
         if (w[i].high > high) { 
             high=w[i].high;
             index_h = i;
         }
         if (w[i].low < low) {
             low = w[i].low;
             index_l = i;
         }
     }
     cout << "Total rainfall is: " << ttl_rain << endl;
     cout << "Average rainfall is: " << ttl_rain / size << " inches\n";
     cout << "High temp was " << high << ". Occured in " << months[index_h];
     cout << endl;
     cout << "Low temp was " << low << ". Occured in " << months[index_l];
     cout << endl;
 }
 
 // user enters how much was spent on each monthly budget category
 void spent(MonthlyBudget *mb) {
     // bugdget only contains
     for (int i = 0; i != mb->size; ++i) {
         cout << "How much was spent on " << mb->expense[i] << ": ";
         cin >> mb->budget[i];
     }
     cout << endl;
 }
 
 void cmpBudg(MonthlyBudget * deflt, MonthlyBudget *actual) {
     for (int i = 0; i != 10; ++i) {
         if ( actual->budget[i] > deflt->budget[i]) 
             cout << "You spent $"<< actual->budget[i] - deflt->budget[i]
                  <<  " too much on " << deflt->expense[i] << ".\n";
         else
             cout << "You were $"<< deflt->budget[i] - actual->budget[i]
                  <<  " under for " << deflt->expense[i] << ".\n";
     }
 } 
 