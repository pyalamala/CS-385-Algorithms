/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Pranav Yalamala
 * Date        : 10/01/21
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

	vector<vector<int>> ways;
	if (num_stairs == 0){
		ways.push_back({});
	}

	for(int i = 1; i < 4; i++){
		if(num_stairs >= i){
			vector<vector<int>> result = get_ways(num_stairs-i);
			for(unsigned int j = 0; j < result.size(); j++){
				result[j].insert(result[j].begin(), i);
				ways.push_back(result[j]);
			}
		}
	}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

	int count = 1;
	int count1 = 1;
	int length  = ways.size();
	while (length / 10 >= 1){
		count1++;
		length = length /10;
	}


	for (unsigned int i = 0; i < ways.size(); i++){
		cout << setw(count1) << count << ". [";
		for(unsigned int j = 0; j < ways[i].size(); j++){
			if(j < ways[i].size() -1){
				cout << ways[i][j]<< ", ";
			}
			else{
				cout << ways[i][j] << "]";
			}
		}
		cout << endl;
		count++;
	}
}

int main(int argc, char * const argv[]) {
	istringstream iss;
	int stairs;
	vector <vector<int>> ways;

	if(argc < 2 || argc > 2){
		cerr << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}

	iss.str(argv[1]);
	if(!(iss >> stairs) || stairs < 1){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}

	ways = get_ways(stairs);
	if (ways.size() == 1){
		cout << ways.size() << " way to climb " << stairs << " stair.";
	}
	else{
		cout << ways.size() << " ways to climb " << stairs << " stairs.";
	}
	cout << endl;
	display_ways(ways);
	return 0;


}
