/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Bharddwaj Vemulapalli
 * Date        : 2/16/2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <sstream>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    
    for (const auto &character: s) {
        //stays the same for the life of that value it takes on
        if(!(character >='a' && character <= 'z')){
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
    unsigned int a = 0;
    //0 corresponds to 97 and 25 corresponds to 122
    
    for (const auto &character: s) {
        //stays the same for the life of that value it takes on
//            cout << "a: " << a << endl;
//            cout << "character: " << character << endl;
//            cout << (a << (character - 97)) & character) << endl ;
        unsigned int shift = 1 << (character - 'a'); //doesn't work if you use char
        if ((a & shift) != 0){
            //this means that there is a duplicate
            return false;
        }
        else{

            a |= shift; //should put the 1 into the bit vector aka the unsigned int

        }
            
            
            
    }
    return true;
    
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    //characters from a to z (ascii value 97 to 122) are lowercase characters.
    istringstream iss;
    if(argc >2 || argc == 1){
        cerr << "Usage: ./unique <string>" <<endl;
        return 1;
    }
    iss.str(argv[1]);
    string s = argv[1];
    string &a = s;
    //cout <<  s <<endl;
    if(!is_all_lowercase(a)){
        cerr << "Error: String must contain only lowercase letters." << endl;
    }
    else if (all_unique_letters(a)){
        cout << "All letters are unique." << endl;
    }
    else{
        cout << "Duplicate letters found." << endl;
    }
    return 0;
}
