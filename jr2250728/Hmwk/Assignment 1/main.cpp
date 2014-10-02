#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void modProb();
void prob9_2();
void prob9_3();
void prob9_10();
void prob9_12();
void prob9_13();
void menu();
int* mode(int*, int);
float mean(const int *, int);
float median(int *, int);

void fill(int *, int, int = 9);
void printArray(int *, int, int=100);
int* reverse(int *, int);
int* shift(int *, int);
int* expand(int *, int);
int fndMax(int *, int);

int* setFrq(int *, int);
int* modes(int *, int);
int numModes(int *, int size);

int main(int argc, const char * argv[]) {
    int choice;
    
    do {
        menu();
        cin >> choice;
        switch (choice) {
            case(1): modProb();  break;
            case(2): prob9_2();  break;
            case(3): prob9_3();  break;
            case(4): prob9_10(); break;
            case(5): prob9_12(); break;
            case(6): prob9_13(); break;
            case(-1): cout << "Goodbye\n"; break;
            default:
                cout << "Invalid Choice\n";
        }
    } while ( choice != -1);
    
    
    return 0;
}

void menu()
{
    cout << endl;
    cout << string(42, '-') << endl;
    cout << "Type 1 for mode problem presented in class" << endl;
    cout << "Type 2 for problem 9.2" << endl;
    cout << "Type 3 for problem 9.3" << endl;
    cout << "Type 4 for problem 9.10" << endl;
    cout << "Type 5 for problem 9.12" << endl;
    cout << "Type 6 for problem 9.13" << endl;
    cout << "Type -1 to exit" << endl;
    cout << string(42,'-') << endl;
}

void modProb() {
    cout << "Enter the size of the array: ";
    int size;
    cin >> size;
    int *a = new int[size];
    // number for random number generator
    cout << "What is the largest value to use: ";
    int mod;
    cin >> mod;
    
    // numbers to print per line
    cout << "How many numbers to print per line: ";
    int perLine;
    cin >> perLine;
    
    
    fill(a, size, mod);
    
    printArray(a, size, perLine);
    
    int *m = mode(a, size);
    
    delete []a;
    delete []m;
}

void prob9_2() {
    int nGrd;
    cout << "How many grades will be entered: ";
    cin >> nGrd;
    int *grade = new int[nGrd];
    int in;
    for (int i = 0; i != nGrd; ++i) {
        cout << "Enter grade " << i+1 << ": ";
        cin >> in;
        grade[i] = in;
    }
    sort(grade, grade + nGrd);
    cout << endl;
    printArray(grade, nGrd);
    cout << setprecision(4) << mean(grade, nGrd) << endl;
    
    delete []grade;
    
}

void prob9_3() {
    int nGrd;
    cout << "How many grades will be entered: ";
    cin >> nGrd;
    int *grade = new int[nGrd];
    int in;
    for (int i = 0; i != nGrd; ++i) {
        cout << "Enter grade " << i+1 << ": ";
        cin >> in;
        grade[i] = in;
    }
    // lowest grade is the first element of sorted array
    sort(grade, grade + nGrd);

    
    // copy the grades minus the lowest into new array
    int *brray = new int[nGrd-1];
    for (int i = 0; i != nGrd; ++i) {
            brray[i] = grade[i+1];
    }
    
    cout.precision(4);
    sort(brray, brray+nGrd-1);
    printArray(brray, nGrd-1);
    cout << endl;
    cout << mean(brray, nGrd-1) << endl;
    
    delete []grade;
    delete []brray;
}

// Reverse the elements of an array
void prob9_10() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    int *array = new int[size];
    fill(array, size, 100);
    printArray(array, size);
    int *brray = reverse(array, size);
    cout << "Reversed:\n";
    printArray(brray, size);
    
    delete []array;
    delete []brray;
}

// Expand an array to double its size
void prob9_12() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    
    int *array = new int[size];
    fill(array, size);
    
    int *brray = expand(array, size);
    printArray(brray, size*2);
    
    delete []array;
    delete []brray;
    
}

// shifts the values in the array to the right
// a[0] = 1
void prob9_13() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    
    int *array = new int[size];
    fill(array, size);
    
    int *brray = shift(array, size);
    printArray(array, size);
    cout << "Shifted array:\n";
    printArray(brray, size);
    
    delete []array;
    delete []brray;
    
}

int* reverse(int *a, int size ) {
    int *out = new int[size];
    // copy the array
    for (int i = 0; i != size; i++)
        out[i] = a[i];
    
    // swap values at the end with those in front
    for (int i = 0, j = size - 1; i < j; ++i, --j)
    {
        // swap the values
        int temp;
        temp = out[i];
        out[i] = out[j];
        out[j] = temp;
    }
    return out;
}


int* expand(int *a, int size) {
    int newSize = size *2;
    
    int *out = new int[newSize];
    
    for(int i = 0; i != newSize; ++i) {
        if (i < size)
            out[i] = a[i];
        else
            out[i] = 0;
    }
    return out;
}

int* shift(int *a, int size) {
    // create new array
    int *out = new int[size];
    out[0] = 0;
    for(int i = 1; i != size; ++i) {
            out[i] = a[i-1];
    }
    return out;
}

void fill(int *a, int size, int mod) {
    // use current time as seed for random number generator
    srand(time(0));
    for (int i = 0; i != size; ++i) {
        a[i] = rand() % mod + 1;
    }
}

void printArray(int *a, int size, int p) {
    for (int i = 0; i != size; ++i) {
        cout << a[i] << " ";
        if (i % p == p-1)
            cout << endl;
    }
    cout << endl;
}

// find the largest value in an array
int fndMax(int *a, int size) {
    int lrg = a[0];
    for (int i = 1; i != size; ++i) {
        lrg = max(lrg, a[i]);
    }
    return lrg;
}

int* setFrq(int *a, int size) {
    const int OUTSIZE = fndMax(a, size);
    int *out = new int[OUTSIZE+1];
    
    // set counters to zero
    for(int i = 0; i != OUTSIZE; ++i)
        out[i] = 0;
    
    for (int i = 0; i != size; ++i) {
        out[a[i]]++;
    }
    
    return out;
}

// find how many values are repeated maxFreq times
// maxFreq being the number(s) most repeated
int numModes(int *a, int size) {
    int nModes = 0;
    const int maxFreq = fndMax(a, size);
    // numbers must be repeated at least twice to count as a mode
    if (maxFreq > 1) {
        for (int i = 0; i != size; ++i) {
            if (a[i] == maxFreq)
                nModes++;
        }
    }
    else
        nModes = 0;
    return nModes;
}

// takes an array where the index hold the counter of every
// occurance of a number
// e.g if a[2] = 5
// the number 2 was repeated 5 times
int* modes(int *a, int size) {
    // number of modes equal to number of values equal to maxFreq
    int nModes = numModes(a, size);
    
    // create an array equal to the numbers of modes plus two
    // to hold the median and mean
    int *out = new int[nModes + 2];
    
    // first element represents the mean
    // second element represents the media
    int outIndx = 2;
    
    // value of the number repeated the most
    int max = fndMax(a, size);
    if (max == 1)
        return out;

    for (int i = 0; i != size; ++i) {
        if (a[i] == max){
            out[outIndx++] = i;
        }
    }

    return out;
    
}

float mean(const int *a, int size) {
    float sum = 0;
    for (int i = 0; i != size; ++i)
        sum += a[i];

    return sum / size;
}

float median(int *a, int size) {
    // create a copy of original array
    // which is sorted
    int *aCopy = new int [size];
    copy(a, a+size, aCopy);
    
    sort(aCopy, aCopy+size);
    
    // array is an odd size
    // return the middle element
    int mid = size /2;
    if (size%2 == 1)
        return aCopy[mid];
    // array was an even size
    // return average of middle two elements
    return (aCopy[mid] + aCopy[mid-1]) / 2;
}

int* mode(int *a, int size) {
    // b represents the frequencies
    int *b = setFrq(a, size);
    // add 1 to size in order to be able to use the largest value
    // as an index
    int bSize = fndMax(a, size) + 1;
    
    // c represents the complete array
    int *c = modes(b, bSize);
    
    c[0] = mean(a, size);
    c[1] = median(a, size);
    
    // size is +2 because you need it will always include
    int cSize = numModes(b, bSize);
    cout << "\nResult:\n";
    printArray(c,cSize+2);
    
    delete []b;

    return c;
}
