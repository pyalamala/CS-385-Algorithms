/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Yashvardhan Sharma & Pranav Yalamala
 * Date        : 10/15/2021
 * Description : Lists the moves required to fulfill the water jug puzzle.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions) :
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

void print_result(State final){
	if (final.a == -1 && final.b == -1 && final.c ==-1){
		cout << "No solution." << endl;
	}
	else{
		vector<string> output;
		string s;
		State *tracing = &final;
		while (tracing != nullptr){
			s = tracing->directions + tracing->to_string();
			output.push_back(s);
			tracing = tracing->parent;
		}
		while (!output.empty()){
			cout << output.back() << endl;
			output.pop_back();
		}
	}
}

int bfs (int capA, int capB, int capC, int goalA, int goalB, int goalC, int a, int b, int c){
	State s(a, b, c, "Initial state. ");
	State *current;
	State next = {0, 0, 0, ""};
	vector<vector<State*>> array;
	queue<State> *solve = new queue<State>();
	solve->push(s);
	string str;
	for (int i = 0; i <= capA; i++){
		array.push_back({NULL});
		for (int j = 0; j <= capB; j++){
			array[i].push_back({NULL});
		}
	}
	while (!solve->empty()){
		current = new State(solve->front());
		int currentA = current->a;
		int currentB = current->b;
		int currentC = current->c;
		if ((currentA == goalA) && (currentB == goalB) && (currentC == goalC)){
			print_result(*current);
			for (int i = 0; i <= capA; i++){
					for (int j = 0; j <= capB; j++){
						delete array[i][j];
					}
			}
			delete solve;
			return 1;
		}
		solve->pop();
		if (array[currentA][currentB] == NULL){
			array[currentA][currentB] = current;
			//Moving water from C to A
			if (currentC != 0 && currentA != capA){
				if (currentC - (capA - currentA) >= 0){
					a = capA;
					b = currentB;
					c = currentC - (capA - currentA);
					if (a - currentA > 1){
						str = "Pour " + to_string(a-currentA) + " gallons from C to A. ";
					}
					else{
						str = "Pour 1 gallon from C to A. ";
					}
					next = {a, b, c, str};
					next.parent = current;
					solve->push(next);
				}
				else{
					a = currentA + currentC;
					b = currentB;
					c = 0;
					if (currentC > 1){
						str = "Pour " + to_string(currentC) + " gallons from C to A. ";
					}
					else{
						str = "Pour 1 gallon from C to A. ";
					}
					next = {a, b, c, str};
					next.parent = current;
					solve->push(next);
				}
			}
			//Moving from B to A
			if (currentB != 0 && currentA != capA){
				if (currentB - (capA - currentA) >= 0){
					a = capA;
					b = currentB - (capA - currentA);
					c = currentC;
					if (a - currentA > 1){
						str = "Pour " + to_string(a-currentA) + " gallons from B to A. ";
					}
					else{
						str = "Pour 1 gallon from B to A. ";
					}
					next = {a, b, c, str};
					next.parent = current;
					solve->push(next);
				}
				else{
					a = currentA + currentB;
					b = 0;
					c = currentC;
					if (currentB > 1){
						str = "Pour " + to_string(currentB) + " gallons from B to A. ";
					}
					else{
						str = "Pour 1 gallon from B to A. ";
					}
					next = {a, b, c, str};
					next.parent = current;
					solve->push(next);
				}
			}
			//Moving from C to B
			if (currentC != 0 && currentB != capB){
				if (currentC - (capB - currentB) >= 0){
					a = currentA;
					b = capB;
					c = currentC - (capB - currentB);
					if (b - currentB > 1){
						str = "Pour " + to_string(b-currentB) + " gallons from C to B. ";
					}
					else{
						str = "Pour 1 gallon from C to B. ";
					}
					next = {a, b, c, str};
					next.parent = current;
					solve->push(next);
				}
				else{
					a = currentA;
					b = currentB + currentC;
					c = 0;
					if (currentC > 1){
						str = "Pour " + to_string(currentC) + " gallons from C to B. ";
					}
					else{
						str = "Pour 1 gallon from C to B. ";
					}
					next = {a, b, c, str};
					next.parent = current;
					solve->push(next);
				}
			}
			//Moving from A to B
			if (currentA != 0 && currentB != capB){
				if (currentA - (capB - currentB) >= 0){
					a = currentA - (capB - currentB);
					b = capB;
					c = currentC;
					if (b - currentB > 1){
						str = "Pour " + to_string(b-currentB) + " gallons from A to B. ";
					}
					else{
						str = "Pour 1 gallon from A to B. ";
					}
					next = {a, b, c, str};
					next.parent = current;
					solve->push(next);
				}
				else{
					a = 0;
					b = currentB + currentA;
					c = currentC;
					if (currentA > 1){
						str = "Pour " + to_string(currentA) + " gallons from A to B. ";
					}
					else{
						str = "Pour 1 gallon from A to B. ";
					}
					next = {a, b, c, str};
					next.parent = current;
					solve->push(next);
				}
			}
			//Moving from B to C
			if (currentB != 0 && currentC != capC){
				if (currentB - (capC - currentC) >= 0){
					a = currentA;
					b = currentB - (capC - currentC);
					c = capC;
					if (c - currentC > 1){
						str = "Pour " + to_string(c-currentC) + " gallons from B to C. ";
					}
					else{
						str = "Pour 1 gallon from B to C. ";
					}
					next = {a, b, c, str};
					next.parent = current;
					solve->push(next);
				}
				else{
					a = currentA;
					b = 0;
					c = currentC + currentB;
					if (currentB > 1){
						str = "Pour " + to_string(currentB) + " gallons from B to C. ";
					}
					else{
						str = "Pour 1 gallon from B to C. ";
					}
					next = {a, b, c, str};
					next.parent = current;
					solve->push(next);
				}
			}
			//Moving from A to C
			if (currentA != 0 && currentC != capC){
				if (currentA - (capC - currentC) >= 0){
					a = currentA - (capC - currentC);
					b = currentB;
					c = capC;
					if (c - currentC > 1){
						str = "Pour " + to_string(c-currentC) + " gallons from A to C. ";
					}
					else{
						str = "Pour 1 gallon from A to C. ";
					}
					next = {a, b, c, str};
					next.parent = current;
					solve->push(next);
				}
				else{
					a = 0;
					b = currentB;
					c = currentC + currentA;
					if (currentA > 1){
						str = "Pour " + to_string(currentA) + " gallons from A to C. ";
					}
					else{
						str = "Pour 1 gallon from A to C. ";
					}
					next = {a, b, c, str};
					next.parent = current;
					solve->push(next);
				}
			}

		}
		else{
			delete current;
		}

}
		cout << "No solution.";
		for (int i = 0; i <= capA; i++){
			for (int j = 0; j <= capB; j++){
			delete array[i][j];
			}
		}
	delete solve;
	return 1;
}

int main(int argc, char * const argv[]) {
	int capA, capB, capC, goalA, goalB, goalC;

	istringstream iss;

	if (argc > 7 || argc < 7){
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if (!(iss >> capA) || capA <= 0){
		cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if (!(iss >> capB) || capB <= 0){
		cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[3]);
	if (!(iss >> capC) || capC <= 0){
		cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[4]);
	if (!(iss >> goalA)){
		cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
		return 1;
	}
	else if (goalA < 0){
		cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
		return 1;
	}

	iss.clear();
	iss.str(argv[5]);
	if (!(iss >> goalB)){
		cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
		return 1;
	}
	else if (goalB < 0){
		cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
		return 1;
	}

	iss.clear();
	iss.str(argv[6]);
	if (!(iss >> goalC)){
		cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
		return 1;
	}
	else if (goalC < 0){
		cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
		return 1;
	}
	if (goalA > capA){
			cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
			return 1;
	}
	if (goalB > capB){
		cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
		return 1;
	}
	if (goalC > capC){
		cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
		return 1;
	}
	if ((goalA + goalB + goalC) != capC){
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}

	bfs(capA, capB, capC, goalA, goalB, goalC, 0, 0, capC);
}



