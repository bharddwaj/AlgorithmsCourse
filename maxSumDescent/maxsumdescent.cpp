/*******************************************************************************
 * Name        : maxsumdescent.cpp
 * Author      : Bharddwaj Vemulapalli
 * Version     : 1.0
 * Date        : 04/26/2020
 * Description : Dynamic programming solution to max sum descent problem.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

const char DELIMITER = ' ';

int **values, // This is your 2D array of values, read from the file.
    **sums;   // This is your 2D array of partial sums, used in DP.

int num_rows; // num_rows tells you how many rows the 2D array has.
              // The first row has 1 column, the second row has 2 columns, and
              // so on...

/**
 * Displays the 2D array of values read from the file in the format of a table.
 */
void display_table() {
    // TODO
    int max_digits = 1;
    for(int i = 0; i < num_rows; i++){
        
        for(int j = 0; j <= i; j++){
            if(values[i][j] > 9){
                //at most we will have 2 digit integers
                max_digits = 2;
                goto star;
            }
        }
        
    }
    star:
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j <= i; j++){
            if (j!=i) {
                //not the last element
                cout <<setw(max_digits) << values[i][j] << " ";
            }
            else{
                 cout << setw(max_digits) << values[i][j];
            }
            
        }
        cout << "\n"; //need the new line after each row
    }

}

/**
 * Returns the maximum sum possible in the triangle of values.
 * By starting at the top of the triangle and moving to adjacent numbers on the
 * row below, this function uses dynamic programming to build up another table
 * of partial sums.
 */
int compute_max_sum() {
    // TODO

    // Populate the 2D array of partial sums. It should still work even if
    // num_rows is 0 (i.e. the file was blank).

    // Loop over the last row to find the max sum.

    // Return the max sum.
    
    if(num_rows == 0){
        return 0;
    }
    else{
        sums[0][0] = values[0][0];
        int maxSum = -1;
        for(int i = 1; i < num_rows; i++){
            for(int j = 0; j <= i; j++){
                
                if(j == 0){
                    sums[i][j] = values[i][j] + sums[i-1][j];
                    if( i == num_rows - 1){
                        maxSum = max(maxSum,sums[i][j]);
                    }
                }
                
                else if(j == i){
                    sums[i][j] = values[i][j] + sums[i-1][j-1];
                    if( i == num_rows - 1){
                        maxSum = max(maxSum,sums[i][j]);
                    }
                }
                else{
                    sums[i][j] = max(values[i][j] + sums[i-1][j-1],values[i][j] + sums[i-1][j]);
                    if( i == num_rows - 1){
                        maxSum = max(maxSum,sums[i][j]);
                    }
                }
            }
           
        }
        if (maxSum == -1) {
            //never entered the loop
            return sums[0][0] ;
        }
        //else
        return maxSum;
        //this below code works but why not just find the max inside the loop instead of having this extra iteration
//        auto iterator_to_max = max_element(sums[num_rows-1],sums[num_rows-1]+num_rows);
//        return *iterator_to_max;
    }
    
   
}

/**
 * Returns a vector of ints with the values from the top to the bottom of the
 * triangle that comprise the maximum sum.
 */
vector<int> backtrack_solution() {
    vector<int> solution;
    // TODO
    if(num_rows == 0){
        return solution;
    }
    else{
        int max_value = sums[num_rows-1][0];
        int max_j_index = 0;
        for(int j = 0; j < num_rows; j++){
            //can do this because the sums 2D array is already filled out
            if(sums[num_rows-1][j] > max_value){
                max_value = sums[num_rows-1][j];
                max_j_index = j;
            }
        }
        //sums[0][0] = values[0][0];
        solution.push_back(values[num_rows-1][max_j_index]);
//        cout << "MAX VALUE: " << values[num_rows-1][max_j_index] << endl;
        int j = max_j_index;
        for(int i = num_rows-1; i > 0; i--){
            //second to last row will be appended and on
            //and > 0 so when it goes backwards from index 1 it hits 0
                if(j == 0){
                    solution.push_back(values[i-1][j]);
                }
                
                else if(j == i){
//                    sums[i][j] = values[i][j] + sums[i-1][j-1];
                    solution.push_back(values[i-1][j-1]);
                    j = j-1;
                }
                else{
//                    sums[i][j] = max(values[i][j] + sums[i-1][j-1],values[i][j] + sums[i-1][j]);
                    if(sums[i-1][j-1] > sums[i-1][j]){ //have to check the sums as opposed to the values or else you may not go in the direction of the greatest sum
                        solution.push_back(values[i-1][j-1]);
                        j = j-1;
                    }
                    else{
                        solution.push_back(values[i-1][j]);
                    }
                   
                }

        }

//        reverse(solution.begin(),solution.end());
//        cout << "Solution size: " << solution.size() << endl;
        return solution;
    }
}

/**
 * Reads the contents of the file into the global 2D array 'values'. If
 * successful, the function also allocates memory for the 2D array 'sums'.
 */
bool load_values_from_file(const string &filename) {
    ifstream input_file(filename.c_str());
    if (!input_file) {
        cerr << "Error: Cannot open file '" << filename << "'." << endl;
        return false;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
    vector<string> data;
    try {
        while (getline(input_file, line)) {
            data.push_back(line);
        }
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }
    
    // TODO
    num_rows = data.size();
    values = new int*[num_rows];
    sums = new int*[num_rows];
    for(int i = 0; i < num_rows; i++){
        values[i] = new int[i+1]; //don't need every array to allocate space of num_rows
        sums[i] = new int[i+1];
    }
    int j = 0;
    for(int i = 0; i < num_rows; i++){
        string num = "";
        for(char &c : data[i]){
            if(c != ' '){
                num += c;
//                j++;
            }
            else{
                int x;
                stringstream ss(num);
                ss >> x;
                values[i][j] = x;
                j++;
                num = "";
            }
        }
        //there is no space after last number so without this it doesnt get inputted into the table
        int x;
        stringstream ss(num);
        ss >> x;
        values[i][j] = x;
        j++;
        num = "";
        j = 0;
    }
    
    return true;
}

/**
 * Frees up the memory allocated for the 2D array of values and the 2D array of
 * partial sums.
 */
void cleanup() {
    // TODO
    for (int i = 0; i < num_rows; i++) {
        delete [] sums[i];
        delete [] values[i];
    }
    delete [] sums;
    delete [] values;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    string filename(argv[1]);
    if (!load_values_from_file(filename)) {
        return 1;
    }

    // TODO
    display_table();
    cout << "Max sum: " << compute_max_sum() << endl;
    vector<int> solution = backtrack_solution();
    cout << "Values: [";
    for (int i = num_rows-1; i >= 0; i--) {
        if(i > 0){
            cout << to_string(solution[i]) + ", ";
        }
        else{
             cout << to_string(solution[i]);
        }
        
    }
    
    cout << "]" <<endl;
//    reverse(solution.begin(),solution.end());
//    cout << "Values: [";
//    for (int i = 0; i < num_rows; i++) {
//        if(i < num_rows-1){
//            cout << to_string(solution[i]) + ", ";
//        }
//        else{
//             cout << to_string(solution[i]);
//        }
//
//    }
//    cout << "]" <<endl;
    cleanup();
    return 0;
}
