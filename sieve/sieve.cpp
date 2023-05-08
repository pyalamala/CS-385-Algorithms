/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Pranav Yalamaa
 * Date        : 09/13/21
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honors System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

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
        	is_prime_[0] = false;
        	is_prime_[1] = false;

        	for(int i = 2; i< limit_ + 1; i++){
        		is_prime_[i] = true;
        	}
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.

	cout << endl;
	cout << "Number of primes found: " << count_num_primes() << endl;
	cout << "Primes up to " << limit_ << ":" << endl;

	const int max_prime_width = num_digits(max_prime_),
			primes_per_row = 80 / (max_prime_width + 1);

	int count = 0;

	for(int i = 2; i < limit_ + 1; i++){
		if (count == primes_per_row){
			count = 0;
			cout << endl;
		}

		if(is_prime_[i]){


			if (count_num_primes() > primes_per_row){
				if(count == 0){
					cout << setw(max_prime_width) << i;
				}
				else {
					cout << setw(max_prime_width + 1) << i;
				}
			}
			else{
				if(count == 0){
					cout << i;
				}
				else{
					cout << " " << i;
				}
			}

			count++;
		}
	}

	cout << endl;
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
	int num_primes = 0;

	for(int i = 2; i < limit_ + 1; i++){
		if(is_prime_[i]){
			num_primes ++;
		}
	}
    return num_primes;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
	for(int i = 2; i < sqrt(limit_); i++){
		if(is_prime_[i]){
			for(int j = pow(i, 2); j <= limit_; j += i){
				is_prime_[j] = false;
			}
		}
	}

	for(int i = limit_; i >= 2; i--){
		if(is_prime_[i]){
			max_prime_ = i;
			break;
		}
	}


}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.

	return int(log10(num) + 1);
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
    PrimesSieve sieve(limit);
    sieve.display_primes();

    return 0;
}
