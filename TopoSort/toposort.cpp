/*
 * toposort.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: user
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

vector<int> toposort(vector<int> graph [], int V){
	int *indegree = new int[V];
	fill(indegree, indegree + V, 0);
	for(int v1 = 0, vq < V; v1++){
		for(int v2: graph[v1] ){
			indegree[v2]++;
		}
		/*
		for(size_t j = 0; graph[v1].size(); j++){
			int v2 = graph[v1][j];
			indegree[v2]++;
		}
		*/
	}
	
	vector<int> L;
	
	queue<int> S;
	for(int v = 0; v < V; v++){
		if(indegree [v] == 0){
			S.push(v);
		}
	}

	while(!S.empty()){
		int vertex = S.front();
		S.pop();
		L.push_back(vertex);
		for(int v2: graph[vertex]){
			indegree[v2]--;
			if(indegree[v2] == 0){
				S.push(v2);
			}
		}
	}

	for(int v = 0; v < V; v++){
		if(indegree[v] != 0){
			L.clear();
			break;
		}
	}

	delete[] indegree;
	return L;


}

int main(){
	int V, E;
	cin >> V >> E;
	vector<int> *graph = new vector<int>[V];

	while(E--){
		int v1, v2;
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
	}
	vector<int> = toposort(graph, V);


}





