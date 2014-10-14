/*
*    Ruiz, Juan - Assignment 3 - 48130
*/
#include <iostream>
#include <string>
#include <iomanip>
#include "Structures.h"
using namespace std;

/* Sructures are here */

// structure for problem 11.1


/*
 * Prototypes begin here
 */

void prob11_1();
void prntMov(const Movie&);

int main() {
    prob11_1();

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