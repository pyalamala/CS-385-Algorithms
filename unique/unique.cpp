/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Pranav Yalamala
 * Date        : 9/25/21
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

	for (const auto &c : s){
		if (c < 'a' || c > 'z'){
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

	int bit = 0;
	for(const auto &c: s){
		int car = 1 << (c - 'a');
		if(car & bit){
			return false;
		}
		bit = car | bit;
	}
	return true;


}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
	istringstream iss;
	string s;

	if (argc < 2 || argc > 2){
		cerr << "Usage: ./unique <string>" << endl;
		return 1;
	}

	iss.str(argv[1]);
	iss >> s;
	if(!is_all_lowercase(s)){
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}
	iss.clear();

	if(s.length() > 26 || !all_unique_letters(s)){
		cout << "Duplicate letters found." << endl;
	}
	else{
		cout << "All letters are unique." << endl;
	}
	return 0;



}
