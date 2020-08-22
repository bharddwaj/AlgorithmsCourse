/*******************************************************************************
* Name        : final.cpp
* Author      : Bharddwaj Vemulapalli
* Version     : 1.0
* Date        : 05/09/2020
* Description : Final Project
* Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
******************************************************************************/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <unordered_map> //using map vs unordered map

using namespace std;



vector<string> data; //used in the load_values_from_file() function
unordered_map<string,vector<string>> sorted_data; //key is the sorted word in lower case characters while the values are vectors of anagrams

string str_tolower(string s) {
    //I got this from the C++ documentation
    // https://en.cppreference.com/w/cpp/string/byte/tolower
    transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return tolower(c); } // correct
                  );
    return s;
}

bool compareLength(const string& a, const string& b){
    //need this compare function so I can sort the strings
    // in descending order in my vector dictionary of length
    //but i also need those of the same lengths to be sorted properly as well
    if(a.size() != b.size()){
        return (a.size() > b.size());
    }
    else{
        //want to sort alphabetically if they are the same size
        
        for(long unsigned int i = 0; i < min(a.length(),b.length()); i++){
            if(a[i] != b[i]){
                return a[i] < b[i];
            }
        }
        return true;
    }
}

bool load_values_from_file(const string &filename) {
    //gets each string from text file and places it into the vector
    ifstream input_file(filename.c_str());
    if (!input_file) {
        cerr << "Error: File '" << filename << "' not found." << endl;
        return false;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
//    int count = 0;
    bool disregard;
    try {
        while (getline(input_file, line)) {
            
//            arrData[count] = line;
//            count++;
            disregard = false;
            for (char &c: line) {
                //calculating the ascii sum
                if( ( c < 65 && (c != 45 && c != 39) ) || (c > 90 && c < 97) || c > 122  ){
                    // if c is not a hyphen or apostrophe and is less than 65
                    // if c is between Z and ' (exclusive)
                    // if c greater than z
//                    cout << "This word is disregarded: " << line << "\n";
                    disregard = true;
                }
            }
            if(!disregard){
                data.push_back(line);
                string copy = str_tolower(line); // i need the original word to put into the map
                sort(copy.begin(), copy.end()); //in place sorting of the characters
                if ( sorted_data.find(copy) == sorted_data.end() ){
                    //key not found
                    vector<string> scrambled_words; //anagrams vector
                    scrambled_words.push_back(line);
                    sorted_data[copy] = scrambled_words;
                }
                else{
                    //key is found
//                    cout << "key is found meeaning there is defiinitely an anagram" << "\n";
//                    cout << "KEY: " << copy << "\n";
                    sorted_data[copy].push_back(line); //we just simply append to the vector
                }
            }
        }
        input_file.close();
        sort(data.begin(),data.end(),compareLength); //sort the strings
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }
    
    return true;
}
// vector<string> Anagrams(string word){
//    //check if the word can be rewritten as any of the other words in the dictionary
//    //notice the vector is pass by reference because I want to make sure I make changes to it
//     sort(word.begin(),word.end()); // in line sorting
//     return sorted_data[str_tolower(word)];
//}
void printAnagrams(){
    //CALL AT THE END
    //Also REMOVES keys from the map to avoid duplicate prints
    long unsigned int prev_length = 0;
    unsigned int iterationCount = 0; //for the first iteration I need to print length
    bool AnagramsFound = false;
    for (string &a: data) { //remember data is sorted in descending order of longest strings
//        cout << "A: " <<a.length() << "\n" ;
//        cout << "prev: " << prev_length << "\n" ;
        if(a.length() >= prev_length){
            //prints the anagrams of all the
            string word =str_tolower(a); //lowercase word first and then sort!!!!
            sort(word.begin(),word.end());
            
            if(sorted_data.find(word) !=sorted_data.end() ){
                //key is in the map
                vector<string> temp = sorted_data[ word ];
                sort(temp.begin(),temp.end()); // sort the way the anagrams are printed
                
//                prev_length = a.length();
                long unsigned int numAnagrams = temp.size();
//                cout << "NUM anagrams: " << numAnagrams << "\n";
                if(numAnagrams > 1){
                    AnagramsFound = true;
                    prev_length = a.length();
                    if(iterationCount == 0){
                        //number of anagrams has to be more than 1
                        cout << "Max anagram length: " << prev_length << "\n";
                        iterationCount++;
                    }
                    for (long unsigned int i = 0; i < numAnagrams; i++){
                        cout << temp[i] << "\n" ;
                    }
                    cout << "\n";
                }
                
                sorted_data.erase(word); // remove the key from the map
                
            }
            else{
                //key is not in the map
                continue;
            }
            
        }
        else{
            //we don't need to print out any of the other anagrams
            break;
        }
    }
    if(!AnagramsFound ){
        cout << "No anagrams found." << "\n";
    }
}

int main(int argc, char * const argv[]){
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <dictionary file>" << endl;
        return 1;
    }
    string filename(argv[1]);
    if (!load_values_from_file(filename)) {
        return 1;
    }
//    for(string &a : data){
//        cout << a << "\n";
//    }
    
//    for (map<string,vector<string>>::iterator it=sorted_data.begin(); it!=sorted_data.end(); ++it){
//        cout << it->first << "\n";
//    }

    printAnagrams();


    
    return 0;
}
