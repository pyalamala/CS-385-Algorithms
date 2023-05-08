/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Yashvardhan Sharma and Pranav Yalamala
 * Version     : 1.0
 * Date        : 11/28/21
 * Description : Implementation of floyd's algorithm.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;
long INF = LONG_MAX;

long** floyd(long** distances, long vertices){
	long** floydmatrix = distances;
	for (long k = 0; k < vertices; k++){
		for (long i = 0; i < vertices; i++){
			for (long j = 0; j < vertices; j++){
				if (floydmatrix[i][k] != INF && floydmatrix[k][j] != INF){
					floydmatrix[i][j] = min(floydmatrix[i][j], floydmatrix[i][k] + floydmatrix[k][j]);
				}
		}
	}
}
	return floydmatrix;
}

long** intermediate(long** distances, long** intermediates, long vertices){
	long** dist = distances;
	long** intermediatematrix = intermediates;

	for (long k = 0; k < vertices; k++){
			for (long i = 0; i < vertices; i++){
				for (long j = 0; j < vertices; j++){
					if (dist[i][k] != INF && dist[k][j] != INF && i != j){
						if (dist[i][k] + dist[k][j] < dist[i][j]){
							dist[i][j] = dist[i][k] + dist[k][j];
							intermediatematrix[i][j] = k; //add A to k
						}
					}
			}
		}
	}
	return intermediatematrix;
}

//displaying the matrices -> straight from instructions
void display_table(long** const matrix, const string &label,  long num_vertices, const bool use_letters = false) {
    cout << label << endl;
    long max_val = 0;
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            long cell = matrix[i][j];
            if (cell < INF && cell > max_val) {
                max_val = matrix[i][j];
            }
        }
    }

    int max_cell_width = use_letters ? (to_string(max_val)).length() : (to_string(max(static_cast<long>(num_vertices), max_val))).length();
    cout << ' ';
    for (int j = 0; j < num_vertices; j++) {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vertices; i++) {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++) {
            cout << " " << setw(max_cell_width);
            if (matrix[i][j] == INF) {
                cout << "-";
            } else if (use_letters) {
                cout << static_cast<char>(matrix[i][j] + 'A');
            } else {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}


//displaying the path
string print_path(long** intermediates, long i, long j){
	if(intermediates[i][j] == INF){
		string s(1, char('A' + i));
		return s + " -> ";
	}
	return print_path(intermediates, i, intermediates[i][j]) + print_path(intermediates, intermediates[i][j], j);
}
void display_path(long** distances, long** intermediates, long vertices){
	for (long i = 0; i < vertices; i++){
		char printi = (char)(i+65);
		for (long j = 0; j < vertices; j++){
			char printj = (char)(j+65);
			if (distances[i][j] == INF){
				cout << printi << " -> " << printj << ", distance: infinity, path: none";
			}
			else{
				cout << printi << " -> " << printj << ", distance: " << distances[i][j] << ", path: ";
			}
			if(i != j && distances[i][j] != INF){
				string pain = print_path(intermediates, i, j);
				cout << pain << printj;
			}
			else if(distances[i][j] != INF){
				cout << printi;
			}
			cout << endl;
		}
	}
}


void deleteMatrices(long** matrix, long vertices){
	for (long i = 0; i < vertices; i++){
		delete [] matrix[i];
	}
	delete matrix;
}


int main(int argc, char *const argv[]){
	if(argc != 2){
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
		return 1;
	}
	ifstream input_file(argv[1]);
	if(!input_file){
		cerr <<"Error: Cannot open file '" << argv[1] << "'.\n";
		return 1;
	}

	input_file.exceptions(ifstream::badbit);
	string line;
	getline(input_file, line);

	istringstream int_read(line);
	istringstream string_read(line);
	int vertices;
	string v;

	int_read>>vertices;
	string_read>>v;

	if (!(vertices > 0 && vertices <= 26) && to_string(vertices) == v){
		cerr << "Error: Invalid number of vertices '" << vertices << "' on line 1." << endl;
		return 1;
	}

	if (vertices == 0){
		cerr << "Error: Invalid number of vertices '" << v << "' on line 1." << endl;
		return 1;
	}

	//Distance Matrix
	long** distances = new long*[vertices];
	//filling the matrix
	for (long i = 0; i < vertices; i++){
		distances[i] = new long[vertices];
		for (long j = 0; j < vertices; j++){
			if (j != i){
				distances[i][j] = INF; //set everything to infinity
			}
			else{
				distances[i][j] = 0; //set diagonal to 0
			}
		}
	}

	//Paths Matrix
	long** paths = new long*[vertices];
	//filling the matrix -> same as distances
	for (long i = 0; i < vertices; i++){
		paths[i] = new long[vertices];
		for (long j = 0; j < vertices; j++){
			if (j != i){
				paths[i][j] = INF; //set everything to infinity
			}
			else{
				paths[i][j] = 0; //set diagonal to 0
			}
		}
	}

	//Intermediates Matrix
	long** intermediates = new long*[vertices];
	for (long i = 0; i < vertices; i++){
		intermediates[i] = new long[vertices];
		for (long j = 0; j < vertices; j++){
			intermediates[i][j] = INF;
		}
	}



		string V1, V2;
		int W;
	try {
		unsigned int numline = 2;

		while (getline(input_file, line)){
			istringstream in(line);
			istringstream tmp(line);
			string temp1, temp2, temp3;
			in >> V1;
			in >> V2;
			in >> W;
			tmp >> temp1;
			tmp >> temp2;

			if (!(tmp >> temp3)){
				cerr << "Error: Invalid edge data '" << V1 << " " << V2 << "' on line " << numline <<"." << endl;
				return 1;
			}

			else if(V1[0] > '@' + vertices || V1[0] <= '@' || V1.length() > 1){
				cerr << "Error: Starting vertex '" << V1 << "' on line " << numline << " is not among valid values A-" << char('@' + vertices) << "." << endl;
				return 1;
			}
			else if(V2[0] > '@' + vertices || V2[0] <= '@' || V2.length() > 1){
				cerr << "Error: Ending vertex '" << V2 << "' on line " << numline << " is not among valid values A-" << char('@' + vertices) << "." << endl;
				return 1;
			}

			else if(temp3[0] <= '0' || temp3[0] > '9'){
				cerr<< "Error: Invalid edge weight '" << temp3 << "' on line " << numline << "." << endl;
				return 1;
			}
			else{

				distances[int(V1[0] - 'A')][int(V2[0] - 'A')] = W;
				paths[int(V1[0] - 'A')][int(V2[0] - 'A')] = W;
				numline++;
			}
		}
		input_file.close();
	} catch(const ifstream::failure &f){
		cerr << "Error: an I/O error occurred reading '" << argv[1] <<"'." << endl;
		return 1;
	}

	display_table(distances, "Distance matrix:", vertices, false);
	display_table(floyd(distances, vertices), "Path lengths:", vertices, false);
	display_table(intermediate(paths, intermediates, vertices), "Intermediate vertices:", vertices, true);

	display_path(distances, intermediates, vertices);


	deleteMatrices(distances, vertices);
	deleteMatrices(intermediates, vertices);
	deleteMatrices(paths, vertices);
	return 0;
}




