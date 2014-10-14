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
    float total;          // total rainfall
    float high;         // high temp
    float low;          // low temp
    float avg;          // average temp
};
/*
 * Prototypes begin here
 */

void prob11_1();
void prob11_4();

/*
 * Utility functions for assigned problems
 */
void prntMov(const Movie&);
void rdWthr(Weather *, int =12); // 12 months in a year
void calcWthr(Weather *, int = 12);

int main() {
    prob11_4();

    return 0;
} 
// Create a structure holding movie data
// Create two movies
// Print the movie data
 void prob11_1() {
    Movie m1, m2;
    m1.title = "title of 1";
    m1.director = "director of 1";
    m1.released = "release date of 1";
    m1.length = "length of 1";
    
    m2.title = "title of 2";
    m2.director = "director of 2";
    m2.released = "release date of 2";
    m2.length = "length of 2";
    
    prntMov(m1);
    cout << endl;
    prntMov(m2);
    
}
 
 void prntMov(const Movie &m) {
     cout << setw(14) << left << "Title: " << m.title << endl
          << setw(14) << left  << "Director: " << m.director << endl
          << "Release Date: " << m.length << endl
          << "Running Time: " << m.length << endl;
     
 }
 
 void prob11_4() {
     Weather data[12];          // array containing weather data for the year
     rdWthr(data);
     calcWthr(data);
     return;
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
         cout << "Enter the average temperature: ";
         cin >> w[i].avg;
         cout << endl;
     }
     cout << endl;
     
 }
 
 void calcWthr(Weather *w, int size) {
     const char *months[12] = {"January", "February", "March", "April",
                           "May", "June", "July", "August",
                           "September", "October", "November", "December"};
     float avg_rain, ttl_rain=0;        // rainfall
     float high=-100, low = 140, avg;        // temperatures
     int index_h, index_l;              // where high and low temps occured;
     
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
     cout << "Average rainfall is: " << ttl_rain / size << endl;
     cout << "High temp was " << high << ". Occured in " << months[index_h];
     cout << endl;
     cout << "Low temp was " << high << ". Occured in " << months[index_l];
     cout << endl;
 }