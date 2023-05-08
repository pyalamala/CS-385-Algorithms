/*
 * pointers.cpp
 *
 *  Created on: Sep 3, 2021
 *      Author: user
 */

#include <iostream>
#include <iomanip>
using namespace std;

void pass_by_value(int k){
	k =10;
}

void pass_by_pointer(int *k){
	*k = 10; // same as x = 10
}

void pass_by_reference(int &k){ // k becomes a new name for x
	k = 10; // same as x = 10
}

void display_array(int array[], int length){
	for(int i = 0; i < length; i++){
		cout << array[i] << " ";
	}
	cout << endl;
}

void display_array_ptr(int *array, int length){
	for(int *p = array; p < array + length; p++){
		cout << *p << " ";
	}
	cout << endl;
}


int main(){
	int x; // integer
	x = 5;
	int *z; // pointer to an integer
	z = &x; // store the address of x into z
	//int x = 5, *z = &x   one line version of the last bit of code

	cout << x << " " << &x << " " << z << " " << &z << endl;
	cout << "*z is: " << *z << endl;
	//pointer dereference -> *z here lets you go to what the pointer is pointing to
	// If z == &x then *z is the same as x itself
	*z = 7; // x = 7
	cout << x << " " << &x << " " << z << " " << &z << endl;
	cout << "*z is: " << *z << endl;

	pass_by_value(x);
	cout << "x is: " << x << endl;

	pass_by_pointer(&x);
	cout << "x is: " << x << endl;

	x=5;
	pass_by_reference(x);
	cout << "x is: " << x << endl;

	// int a[10] can't use a variable for the length of an array
	int *values = new int[x]; // dynamically create a new array in memory that has a length x, values points to the new array
	for(int i= 0; i < x; i++){
		*(values + i) = i; // values + i * sizeOf(int)(memory size)
		values[i] = i; // easier way to do it, does the same thing, compiler chages this to the first method
	}

	display_array(values, x);
	display_array_ptr(values, x);
	delete [] values; // delete the array when you are done using it


	return 0;
}

