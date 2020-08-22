/*******************************************************************************
* Name        : final.cpp
* Author      : Bharddwaj Vemulapalli
* Version     : 1.0
* Date        : 05/09/2020
* Description : Final Project v2
* Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
******************************************************************************/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <map> //using map vs unordered map
#include <unordered_map>
#include <set>

using namespace std;

struct cmpByStringLength {
    bool operator()(const string& a, const string& b) const {
        if(a.length() != b.length()){
            return (a.length() > b.length());
        }
        else{
            //want to sort alphabetically if they are the same size

            for(long unsigned int i = 0; i < a.length(); i++){ //both lengths are the same
                if(a[i] != b[i]){
                    return a[i] < b[i];
                }
            }
            return a < b;
        }
       
    }
};


//map<string,vector<string>,cmpByStringLength> sorted_data; //key is the sorted word in lower case characters while the values are vectors of anagrams
unordered_map<string,int> numAnagrams;
multimap<string,string,cmpByStringLength> sorted_data2;
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
//                data.push_back(line);
                string copy = str_tolower(line); // i need the original word to put into the map
                sort(copy.begin(), copy.end()); //in place sorting of the characters
               
//                if ( sorted_data.find(copy) == sorted_data.end() ){
//                    //key not found
//                    vector<string> scrambled_words; //anagrams vector
//                    scrambled_words.push_back(line);
//                    sorted_data[copy] = scrambled_words;
//
//                }
//                else{
//                    //key is found
////                    cout << "key is found meaning there is definitely an anagram" << "\n";
////                    cout << "KEY: " << copy << "\n";
//                    sorted_data[copy].push_back(line); //we just simply append to the vector
//
//                }
                sorted_data2.insert(pair<string,string>(line,copy));
                if(numAnagrams.find(copy) == numAnagrams.end()){
                    //key not found
                    numAnagrams[copy] = 1;
                    
                }
                else{
                    numAnagrams[copy]++;
                }
                
            }
        }
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }
    
    return true;
}
//void printAnagrams(){
//    long unsigned int prev_length = 0;
//    unsigned int iterationCount = 0; //for the first iteration I need to print length
//    bool AnagramsFound = false;
//    map<string,vector<string>>::iterator itr;
//    for ( itr = sorted_data.begin(); itr != sorted_data.end(); ++itr){
//        string key = itr->first;
//        if(key.length() >= prev_length){
//            vector<string> temp = itr->second;
//            if( temp.size() > 1){
//                //numAnagrams > 1
//                AnagramsFound = true;
//                prev_length = key.length();
//
//                if(iterationCount == 0){
//                     //number of anagrams has to be more than 1
//                     cout << "Max anagram length: " << prev_length << "\n";
//                     iterationCount++;
//                 }
//                sort(temp.begin(),temp.end());
//                for(long unsigned int i = 0;i < temp.size(); i++ ){
//                    cout << temp[i] << "\n" ;
//                }
//
//                cout << "\n";
//            }
//        }
//        else{
//            //we don't print out any of the other maps
//            break;
//        }
//    }
//    if(!AnagramsFound){
//        //No anagrams were found
//        cout << "No anagrams found." << "\n";
//    }
//}

void printAnagrams2(){
    long unsigned int prev_length = 0;
    unsigned int iterationCount = 0; //for the first iteration I need to print length
    bool AnagramsFound = false;
    multimap <string, string> :: iterator itr;
    for ( itr = sorted_data2.begin(); itr != sorted_data2.end(); ++itr){
//        cout <<sorted_data2.count(itr->first)<< "\n";
        string key = itr->second;
//        cout << key << "\n";
//        cout << sorted_data2.count(key) << "\n";
        if(key.length() >= prev_length){
            //vector<string> temp = itr->second;
            if( numAnagrams[key] > 1){
                //numAnagrams > 1
                AnagramsFound = true;
                prev_length = key.length();
                if(iterationCount == 0){
                    //number of anagrams has to be more than 1
                    cout << "Max anagram length: " << prev_length << "\n";
                    iterationCount++;
                }
//                for(long unsigned int i = 0;i < temp.size(); i++ ){
//                    cout << temp[i] << "\n" ;
//                }
                
                while((itr->second) == key){
                    cout << itr->first << "\n" ;
                    
                    ++itr;
                }
                --itr; //so we don't skip the new key by accident
                //cout << itr->second << "\n" ;
                
                cout << "\n";
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
//    cout << "HELLO WORLD" << "\n";
//    for (map<string,vector<string>>::iterator it=sorted_data.begin(); it!=sorted_data.end(); ++it){
//        cout << it->first << "\n";
//    }

//    printAnagrams();
    printAnagrams2();

    
    return 0;
}
