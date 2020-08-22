/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Bharddwaj Vemulapalli
 * Version     : 1.0
 * Date        : 03/28/2020
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
//static long mergesort(int array[], int scratch[], int low, int high);
static long mergesort(int A[], int scratch [], int lo, int hi);
/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], size_t length) {
    // TODO
    long inversions = 0;
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = i+1; j < length; j++)
        {
            if(array[i]  > array[j]){
                inversions++;
            }
        }
        
    }
    return inversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], const int length) {
    // TODO
    // Hint: Use mergesort!
    int *scratch = new int[length];
    for(int index = 0; index < length; index++){
        scratch[index] = array[index];
    }
    
    long num_inversions = mergesort(array,scratch,0,length-1);
    return num_inversions;
}


//long inversionsGLobal = 0;
static long mergesort(int A[], int scratch [], int lo, int hi) {
    // TODO
    long inversions = 0;
    
    // cout << "(lo: " << lo ;
    // cout << ", hi: " << hi << ")"  <<endl;
    if(lo < hi){
        int mid = lo + (hi - lo) / 2;
        //cout << "mid: " << mid << endl;
        inversions += mergesort(A,scratch, lo, mid);
        inversions += mergesort(A, scratch,mid+1, hi);
        int L = lo;
        int H = mid + 1;
        // cout << "when does this loop happen first" << endl;
        // cout << "(lo: " << lo ;
        // cout << ", hi: " << hi << ")"  <<endl;
        for(int k = lo; k <= hi; k++){
            if(L <= mid && (H > hi or A[L] <= A[H])){
                scratch[k] = A[L];
                L++;
                
            }
            else {
                scratch[k] = A[H];
                // cout << "---------" << endl;
                // cout << A[L] << " > " << A[H] << endl;
                // cout <<  "----------" << endl;
                
                inversions+= H-k;
                //inversionsGLobal+= H-k;
                
                H++;
                
            }
        }
        for(int k = lo; k <= hi; k++){
            A[k] = scratch[k];
        }
    }
    return inversions;
}




int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

    if(argc > 2){
        cerr << "Usage: ./inversioncounter [slow]" <<endl;
        return 1;
    }
  
    if(argc == 2){
        if( strcmp(argv[1],"slow") != 0){ 
            cerr << "Error: Unrecognized option '" << argv[1] <<"'." <<endl;
            return 1;
    
        }
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    
    if(values.size() == 0){
        cerr  << "Error: Sequence of integers not received."<<endl;
        return 1;
    }
    // TODO: produce output
    cout << "Number of inversions: ";
    // if(strcmp(argv[1],"slow") == 0){
    //     cout << count_inversions_slow(values.data(),values.size()) << endl;
    // }
    // else{
    //     cout << count_inversions_fast(values.data(),values.size()) << endl;
    // }
    cout << count_inversions_fast(values.data(),values.size()) << endl;
    // cout << inversionsGLobal << endl;
    
    return 0;
}
