/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Pranav Yalamala and Yashvardhan Sharma
 * Version     : 1.0
 * Date        : 11/28/21
 * Description : Implementation of red-black tree.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int **values, **sums;
int rows, max_sum_index, maximum;

int num_digits(int num){
	if(num / 10 == 0){
		return 1;
	}
	else{
		return 1 + num_digits(num / 10);
	}
}
vector<vector<int>> distance_matrix;
vector<vector<int>> path_lengths;
vector<vector<char>> intermediate_vertices;

bool load_values(const string &name){
	ifstream file(name);
	if(!file){
		cerr <<"Error: Cannot open file '" << name << "'.\n";
		return false;
	}
	file.exceptions(ifstream::badbit);
	string line;
	string V1, V2, W;
	int vertices;
	try{
		unsigned int line_number = 1;
		while(getline(file, line)){
			istringstream iss(line);
			iss >> V1;
			iss >> V2;
			if(line_number == 1){
				if((int(line[0]) - 48) < 1 || (int(line[0]) - 48) > 26){
					cerr <<"Error: Invalid number of vertices '" << line[0] << "' on line " << line_number << "." << endl;
					return false;
				}
				vertices = int(line[0]) - 48;
				line_number++;
				for(int i = 0; i < vertices; i++){
					for(int j = 0; j < vertices; j++){
						distance_matrix[i][j] = nullptr;
						path_lengths[i][j] = 0;
						intermediate_vertices[i][j] = nullptr;
						if(i == j){
							distance_matrix[i][j] = 0;
						}
					}
				}

			}
			else if(!(iss >> W)){
				cerr << "Error: Invalid edge data '" << line[0] << " " << line[2] << "' on line " << line_number <<"." << endl;
				return false;
			}
			else if(V1[0] > '@' + vertices || V1[0] < '@' || V1.length() > 1){
				cerr << "Error: Starting vertex '" << V1 << "' on line " << line_number << " is not among the valid values A-" << char('@' + vertices) << "." << endl;
				return false;
			}
			else if(V2[0] > '@' + vertices || V2[0] < '@' || V2.length() > 1){

				cerr << "Error: Starting vertex '" << V2 << "' on line " << line_number << " is not among the valid values A-" << char('@' + vertices) << "." << endl;
				return false;
			}
			else if(W[0] == '-'){
				cerr<< "Error: Invalid edge weight '" << W << "' on line " << line_number << "." << endl;
				return false;
			}
			else{
				distance_matrix[int(V1) - 64][int(V2) - 64] = W;
				line_number++;
			}
		}
		file.close();
	} catch(const ifstream::failure &f){
		cerr << "Error: an I/O error occurred reading '" << name <<"'." << endl;
		return false;
	}

	return true;



}

int main(int argc, char *const argv[]){
	if(argc != 2){
		cerr << "Usage: " << argv[0] << "<filename>" << endl;
		return 1;
	}
	string filename(argv[1]);
	if(!load_values(filename)){
		return 1;
	}
}




