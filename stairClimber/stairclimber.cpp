/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Bharddwaj Vemulapalli
 * Date        :  February 28, 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    
    vector<vector<int>> ways = {};
    if (num_stairs <= 0){
        //vector<int> empty;
        ways.push_back({});
    }
    else{
        vector< vector<int> >result;
        for(int i = 1; i < 4; i++){
            //1,2, or 3 steps
            if (num_stairs >= i){
                result = get_ways(num_stairs - i);
                //result[j].insert(0, i);
                for(auto &j: result){
                    //result = [ [],[],[],[],[] ]
                    //result[j].insert(0, i);
                    j.insert(j.begin(), i);
                    ways.push_back(j);
                }
                
            }
        }
    }
    return ways;
}


void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int count = 1;
    int innerLoopCounter = 0;
    const int widthWaysSize = log10(ways.size()) + 1;
    for(auto it : ways){
        //not regular .begin() because it is a const vector
        //whenever we deal with collections class, recommend using a preincrement operator
        //if u did post increment it needs to save the state and call something (requires more steps)
        string disp = "";
        cout << setw(widthWaysSize) << count << ". ";
        disp += "[";
        const int size = it.size();
        for (auto inside : it) {
            if(innerLoopCounter < size-1){
                disp += to_string(inside) + ", ";
            }
            else{
                disp += to_string(inside);
            }
            innerLoopCounter++;
        }
        disp += "]";
        cout << disp << endl;
        count ++;
        innerLoopCounter = 0;
    }
}

int main(int argc, char * const argv[]) {
    istringstream iss;
    int num_Stairs;
    
    if(argc != 2){
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }
    iss.str(argv[1]);
    if(!(iss >> num_Stairs)){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    
    else{
        iss >> num_Stairs;
        if(num_Stairs <= 0){
            cerr << "Error: Number of stairs must be a positive integer." << endl;
            return 1;
        }
        if(num_Stairs == 1){
            cout << "1 way to climb 1 stair." << endl;
            cout << "1. [1]" << endl;
        }
        else{
            iss.clear();
            vector<vector<int>> ways =get_ways(num_Stairs);
            cout << (int)(ways.size()) << " ways to climb " << num_Stairs << " stairs."  <<endl;
            display_ways(ways);
        }
        return 0;
    }
}
