/*******************************************************************************
* Name    : sqrt.cpp
* Author  : Bharddwaj Vemulapalli
* Version : 1.0
* Date    : January 27, 2020
* Description : Computes the square root using Newton's approximation algorithm
* Pledge : I pledge my honor that I have abided by the Stevens Honor System.
******************************************************************************/
/**
 Algorithm:
     Return numeric_limits<double>::quiet_NaN(), if the num < 0.  This constant is found in the limits header.
     Return num, if num is 0 or 1.
     Repeat next_guess = (last_guess + num/last_guess) / 2 until abs(last_guess - next_guess) <= epsilon.
     Ultimately, return the last value of next_guess.
 */
#include<iostream>
#include<sstream>
#include<limits> // for NaN
#include <iomanip> //for setprecision

using namespace std;
double actualAlgorithm(double last_guess, double next_guess, const double num,const double epsilon){
    if(abs(last_guess - next_guess) <= epsilon){
        //cout << "Last Guess: " << last_guess << endl;
        //cout << "Next Guess: " << next_guess << endl;
        //cout << "Error: " << abs(last_guess - next_guess) << endl;
        return next_guess;
    }
    else{
        //cout << "Last Guess: " << last_guess << endl;
        double temp = next_guess; //prev_next_guess
        //cout << "Temp: " << temp << endl;
        last_guess = temp;
        next_guess = ((double)(last_guess + num/last_guess)) / ((double)(2));
        //cout << "Next Guess: " << next_guess << endl;
        
        //cout << "Last Guess: " << last_guess << endl;
        return actualAlgorithm(last_guess,next_guess,num,epsilon);
         
    }
}
double sqrt(double num, double epsilon){
    
    if(num < 0){
        return numeric_limits<double>::quiet_NaN();
    }
    else if(num == 0 || num == 1){return num;}
    else{
               
        const double intialLastGuess = num;
        const double initialNextGuess = ((intialLastGuess + num/intialLastGuess)) / ((double)(2));
        //cout << "Initial Last Guess: " << intialLastGuess << endl;
        //cout << "Initial Next Guess: " << initialNextGuess << endl;
        const double approximation = actualAlgorithm(intialLastGuess,initialNextGuess,num,epsilon);
        //cout << "The Square Root Approximation of " << num << " is: " << setprecision(8) << approximation << endl;
        return approximation;
               
    }
       
}
int main(int argc,char *argv[]){
    double num;
    double epsilon;
    istringstream iss;
    
    bool numValid = true;
    
    if(argc != 3 && argc != 2){
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" <<endl;
        return 1;
    }
    
    iss.str(argv[1]);
    if( !(iss >> num)){
        numValid = false;
        cerr << "Error: Value argument must be a double." << endl;
        return 1;
    }
    iss.clear(); //clears internal flags
    epsilon = 1e-7;
    if(argc == 3){
        iss.str(argv[2]);
        if( !(iss >> epsilon)){
            // epsilon = 1e-7;
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
        else{
            if(epsilon < 0 || epsilon == 0){
                cerr << "Error: Epsilon argument must be a positive double." << endl;
                return 1;
            }
        }
        iss.clear();
    }
    
   
    if (numValid){
        cout << fixed << setprecision(8) << sqrt(num,epsilon);
    }
    return 0;
    
}
