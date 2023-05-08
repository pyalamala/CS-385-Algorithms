/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Pranav Yalamala
 * Version     : 1.0
 * Date        : 10/24/21
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long merge(int array[], int scratch[], int low, int mid, int high){
	int l = low, m = mid + 1, h = low;
	int long inversions = 0;
	while(l <= mid && m <= high){
		if(array[l] <= array[m]){
			scratch[h++] = array[l++];
		}
		else{
			scratch[h++] = array[m++];
			inversions += mid + 1 - l;
		}
	}


	while(l <= mid){
		scratch[h++] = array[l++];
	}
	while(m <= high){
		scratch[h++] = array[m++];
	}


	for(int k = 0; k <= high; k++){
		array[k] = scratch[k];
	}

	return inversions;
}

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
	int long inversions = 0;
	for(int i = 0; i < length; i++){
		for(int j = i +1; j < length; j++){
			if (array[j] < array [i]){
				inversions ++;
			}
		}
	}
	return inversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
	int mid;
	int long inversions = 0;
	if(high > low){
		mid = low + (high - low)/2;
		inversions += mergesort(array, scratch, low, mid);
		inversions += mergesort(array, scratch, mid + 1, high);

		inversions += merge(array, scratch, low, mid, high);
	}
	return inversions;
}

long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
	int * temp = new int[length];
	int long inversions = mergesort(array, temp, 0, length - 1);
	delete[] temp;
	return inversions;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

	if (argc > 2) {
		cerr << "Usage: " << argv[0] << " [slow]";
		return 1;
	}

	string slow;
	if(argc == 2 && (slow = argv[1]).compare("slow") != 0){
		cerr << "Error: Unrecognized option '" << slow << "'.";
		return 1;
	}

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;

    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if(values.size() == 0){
    	cerr << "Error: Sequence of integers not received." << endl;
    	return 1;
    }


    // TODO: produce output
    if(slow.compare("slow") == 0){
    	cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
    }
    else{
    	cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
    }


    return 0;
}
