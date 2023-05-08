/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Pranav Yalamala
 * Version : 1.0
 * Date    : September 2, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>
using namespace std;

double sqrt(double num, double epsilon){
	double last_guess = 0;
	double next_guess = num;

	if (num < 0){
		return numeric_limits<double>::quiet_NaN();
	}
	else if (num == 0 || num == 1){
		return num;
	}
	else{
		while(abs(last_guess - next_guess) > epsilon){
			last_guess = next_guess;
			next_guess = (last_guess + num/last_guess)/2;
		}
		return next_guess;
	}


}
int main(int argc, char* argv[]){
	double m,n;
	istringstream iss;
	if (argc < 2 || argc > 3){
		cerr <<"Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}

	iss.str(argv[1]);
	if(!(iss >> m)){
		cerr << "Error: Value argument must be a double." << endl;
		return 1;
	}

	iss.clear();
	if (argc == 3){
		iss.str(argv[2]);
		if(!(iss >> n)){
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
		if( n <= 0){
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
	}
	else{
		n = 1e-7;
	}
	cout << fixed;
	cout << setprecision(8) << sqrt(m,n) << endl;

	return 0;

}



