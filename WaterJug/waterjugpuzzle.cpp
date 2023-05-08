/*******************************************************************************
 * Name        : waterjug.cpp
 * Author      : Pranav Yalamala & Yashvardhan Sharma
 * Date        : 10/15/21
 * Description : Lists the moves required to solve the water jug puzzle.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iomanip>

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

	bool equals(const State &state) const{
		if(a != state.a || b != state.b || c != state.c){
			return false;
		}
		return true;
	}
};

vector <vector <State>> array;
State *size = nullptr;

State pour(State &current, int from, int to){
	int *f, *t, cap, temp, a, b, c;
	char first, last;

	a = current.a;
	b = current.b;
	c = current.c;

	if(from == 2){
		f = &current.c;
		first = 'C';
	}
	else if(from == 1){
		f = &current.b;
		first = 'B';
	}
	else if(from == 0){
		f = &current.a;
		first = 'C';
	}

	if(to == 2){
		t = &current.c;
		cap = size->c;
		last = 'C';
	}
	else if(to == 1){
		t = &current.b;
		cap = size->b;
		last = 'B';
	}
	else if(to == 0){
		t = &current.a;
		cap = size->a;
		last = 'A';
	}

	//pours
	if(*f >= (*t - cap)){
		*f = *f - (*t - cap);
		temp = cap - *t;
		*t = cap;
	}
	else{
		*t = *f + *t;
		temp = *f;
		int i = 0;
		*f = i;
	}
	//sets a,b,c to the new current values
	if(from == 0){
		a = *f;
	}
	else if(from == 1){
		b = *f;
	}
	else if(from == 2){
		c = *f;
	}

	if(to == 0){
		a = *t;
	}
	else if(to == 1){
		b = *t;
	}
	else if(to == 2){
		c = *t;
	}

	if(array[a][b] == nullptr){
		State *s = new State(a, b, c, "");
		if(temp != 1){
			cout << "Pour " << temp << "gallons from " << first << " to " << last << ". (" << a << ", " << b << ", " << c <<")" << endl;
		}
		else{
			cout << "Pour " << temp << "gallon from " << first << " to " << last << ". (" << a << ", " << b << ", " << c <<")" << endl;
		}

		s->parent = *current;
		array[a][b] = s;
		return s;
	}
	return nullptr;
}


State bfs(State *initial, const State &goal){
	queue<State*> queue;
	State *current = initial;
	State *temp = nullptr;
	queue.push(initial);

	while(!queue.empty() && current->equals(goal)){
		current = queue.front();
		queue.pop();

		for(int i = 0; i < 3; i++){
			for(int j = 2; j >= 0; j--){
				if(i != j){
					temp = pour(*current, j, i);
					if(temp != nullptr){
						queue.push(temp);
						if(temp->equals(goal)){
							delete queue;
							return temp;
						}
					}
				}
			}
		}
	}
	delete queue;
	return nullptr;

}

void print_path(State *state){
	if(state->parent){
		print_path(state->parent);
	}

	cout << state->directions << endl;
}


int main(int argc, char * const argv[]) {

	istringstream iss;
	int caps[3], goals[3];
	vector <vector<int>> ways;

	if(argc < 7 || argc > 7){
		cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	for(int i = 1; i < 4; i++){
		iss.str(argv[i]);
		if(!(iss >> caps[i-1]) || caps[i-1] < 1){
			if(i == 1){
				cerr << "Error: Invalid capacity '" << argv[i] <<"' for jug A." << endl;
				return 1;
			}
			else if(i == 2){
				cerr << "Error: Invalid capacity '" << argv[i] <<"' for jug B." << endl;
				return 1;
			}
			else if(i == 3){
				cerr << "Error: Invalid capacity '" << argv[i] <<"' for jug C." << endl;
				return 1;
			}
		}
		iss.clear();
	}

	for(int i = 4; i < 7; i++){
			iss.str(argv[i]);
			if(!(iss >> goals[i-3]) || goals[i-3] < 1){
				if(i == 1){
					cerr << "Error: Invalid goal '" << argv[i] <<"' for jug A." << endl;
					return 1;
				}
				else if(i == 2){
					cerr << "Error: Invalid goal '" << argv[i] <<"' for jug B." << endl;
					return 1;
				}
				else if(i == 3){
					cerr << "Error: Invalid goal '" << argv[i] <<"' for jug C." << endl;
					return 1;
				}
			}
			iss.clear();
		}

	if(caps[3] != goals[0] + goals[1] + goals[3]){
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C";
	}

	size = new State(caps[0], caps[1], caps[2], "Jug Sizes");

	State *goal(goal[0], goal[1], goal[2]);

	array.push_back({});
	for (int i = 0; i < caps[0] + 1; i++){
		array[i].insert();
		for(int j = 0; j < caps[1] + 1; j++){
			array[i][j] = nullptr;
		}
	}




	State *initial(0, 0, caps[2], "Initial state.");
	cout << initial->to_string() << endl;

	State *solution = bfs(initial, *goal);

	if(solution == nullptr){
		cout << "No solution." << endl;
	}
	else{
		print_path(solution);
	}

	for (int i = 0; i < caps[0] + 1; i++){
		for(int j = 0; j < caps[1] + 1; j++){
			delete array[i][j];
		}
	}



	return 0;
}
