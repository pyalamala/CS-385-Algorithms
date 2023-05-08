/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Pranav Yalamala
 * Version : 1.0
 * Date    : September 9, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iomanip>
#include<iostream>
#include<vector>
using namespace std;

class student{
	public:

	student(string f, string l, float gpa, int id) : first_{f}, last_{l}, gpa_{gpa}, id_{id} { }

	string full_name(){
		return first_ + last_;
	}

	int id() const{
		return id_;
	}

	float gpa() const{
		return gpa_;
	}

	void print_info() const{
		cout << fixed;
		cout<< setprecision(2) << first_ << " " << last_ << ", GPA: " << gpa_ << ", ID: " << id_ << endl;
	}




	private:
		string first_, last_;
		float gpa_;
		int id_;
};

/**
		* Takes a vector of Student objects, and returns a new vector
		* with all Students whose GPA is < 1.0.
		*/
	vector<student> find_failing_students(const vector<student> &students){
		vector<student> failing_students;

		//Iterates through the students vector, appending each student whose gpa is less than 1.0
		// to the failing_students vector.

		for(const auto &student : students){
			if(student.gpa() < 1.0){
				failing_students.push_back(student);
			}
		}

		return failing_students;

	}

	void print_students(const vector<student> &students){
		for(const auto &student : students){
			student.print_info();
		}

	}

	/**
	* Allows the user to enter information for multiple students, then
	* find those students whose GPA is below 1.0 and prints them to the
	* screen.
	*/
	int main() {
	    string first_name, last_name;
	    float gpa;
	    int id;
	    char repeat;
	    vector<student> students;
	    do {
	        cout << "Enter student's first name: ";
	        cin >> first_name;
	        cout << "Enter student's last name: ";
	        cin >> last_name;
	        gpa = -1;
	        while (gpa < 0 || gpa > 4) {
	            cout << "Enter student's GPA (0.0-4.0): ";
	            cin >> gpa;
	        }
	        cout << "Enter student's ID: ";
	        cin >> id;
	        students.push_back(student(first_name, last_name, gpa, id));
	        cout << "Add another student to database (Y/N)? ";
	        cin >> repeat;
	    } while (repeat == 'Y' || repeat == 'y');
	    cout << endl << "All students:" << endl;
	    print_students(students);
	    cout << endl << "Failing students:";
	    // TODO
	    // Print a space and the word 'None' on the same line if no students are
	    // failing.
	    // Otherwise, print each failing student on a separate line.
	    if(find_failing_students(students).empty()){
	    	cout << " None" << endl;
	    }
	    else{
	    	cout<< endl;
	    	print_students(find_failing_students(students));
	    }
	    return 0;
	}






