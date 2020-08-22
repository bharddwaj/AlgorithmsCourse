/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Bharddwaj Vemulapalli
 * Date        : 2/3/2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
// echo 200 | ./sieve > output.txt
using namespace std;

class PrimesSieve {
    public:
        PrimesSieve(int limit);

        ~PrimesSieve() {
            delete [] is_prime_;
        }

        int num_primes() const {
            return num_primes_;
        }

        void display_primes() const;
        
    private:
        // Instance variables
        bool * const is_prime_;
        const int limit_;
        int num_primes_, max_prime_;

        // Method declarations
        int count_num_primes() const;
        void sieve();
        static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    cout << endl;
    const int num_primes =count_num_primes();
    cout << "Number of primes found: " << num_primes << endl;
    cout << "Primes up to " << limit_ << ":" << endl;
    
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
    int count = 0;
    for (int i = 2; i <= limit_; i++) {
        if (is_prime_[i]) {
            count++;
            if(((double)num_primes)/((double)primes_per_row) <= 1.0){
                if(count != num_primes){
                    cout << i << " ";
                }
                else{
                    cout << i;
                    
                }
            }
            else if (count % primes_per_row == 0) {
                cout << setw(max_prime_width) << i << endl;
               
            }
            else{
                
                cout <<setw(max_prime_width) << i;
                if(count != num_primes){
                    cout << " ";
                }
                
                
            }
        }
    }
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    int count = 0;
    for (int i = 0; i <= limit_; i++) {
        if (is_prime_[i]) {
            count++;
        }
    }
    return count;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    for(int i = 2; i <= limit_; i ++){
        is_prime_[i] = true;
    }
    for (int i = 2; i <= sqrt(limit_); i++) {
        if (is_prime_[i]){
            for (int j = i+1; j <= limit_; j++) {
                if(j % i == 0){
                    is_prime_[j] = false;
                }
            }
        }
    }
    max_prime_ = limit_;
    while (!is_prime_[max_prime_]) {
        max_prime_--;
    }
    
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int digits = 0;
    while(num!=0){
        num = ((int)(num))/((int)(10));
        digits++;
    }
    return digits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve p1(limit);
    p1.display_primes();
 
    return 0;
}
