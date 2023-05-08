//============================================================================
// Name        : LAB4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
using namespace std;
#include <iostream>



int mystery1(int x, int y){
	int s, c;
	s = x^ y;
	c = x & y;
	while (c != 0){
		c = c << 1;
		x = s;
		y = c;
		s = x^y;
		c = x & y;
	}
	return s;
}

int main(void) {
	cout << mystery1(5, 7) << endl;
	cout << mystery1(2, 8) << endl;
	return 0;

}

