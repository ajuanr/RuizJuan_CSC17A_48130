/* 
 * File:   main.cpp
 * Author: rcc
 *
 * Created on September 16, 2014, 9:35 AM
 */

#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int median(int[], int);
float mean(const int[], int);
int* mode(int[], int);

int* fndFreq(int[], int);
int fndMax(int [], int);

/*
 *   These functions are for testing
 */
int* fillArray(int);
void print(int[], int size);
/*
 * 
 */
int main(int argc, char** argv) {
    const int SIZE = 20;
    int *a = fillArray(SIZE);
    print(a, SIZE);
    //sort(a, a+SIZE);
    //print(a, SIZE);
    cout << median(a, SIZE) << endl;
    cout << mean(a, SIZE) << endl;
    int *b = mode(a, SIZE);
    
    int q[SIZE] = {};
    return 0;
}

// calculate the mean of an array of ints
float mean(const int a[], int size) {
    int sum = 0;
    for (int i = 0; i != size; ++i)
        sum += a[i];
    cout << sum << endl;
    return static_cast<float>(sum) / size;
}

// calculate the median of an array of ints
int median(int a[], int size) {
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

int* mode(int a[], int size) {
    int *mArray = new int [size + 2];
    mArray[0] = mean(a, size);
    mArray[1] = median(a, size);
    
    const int MSIZE = size +1;
    int modes[MSIZE] = {};
    for(int i = 0; i != size; ++i) {
        modes[a[i]]++;
    }
    
    for (int i = 2; i != size+2; ++i) {
        mArray[i] = modes[i];
    }
    print(mArray, size+2);
}

int* fndFreq(int in[], int size) {
    const int MAX  = fndMax(in, size);
    int *out = new int[MAX+1];
    
    for (int i = 0; i != size; ++i) {
        out[in[i++]++;
    }
    
}

int* fillArray(int size) {
    int* a = new int[size];
    
    for(int i = 0; i != size; ++i)
        // fill with numbers from 1 to 10;
        a[i] = rand() % 10 + 1;
    return a;
}

void print(int a[], int size) {
    cout << a[0];
    for (int i = 1; i != size; ++i)
        cout << " " << a[i];
    
    cout << endl;
}