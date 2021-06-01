#ifndef _LIB_H_
#define _LIB_H_
#define INF 999999

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

void printMatrix(int** M, int V) {
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; ++j)
			cout << M[i][j] << "\t";
		cout << endl;
	}
}

void printList(vector<pair<int, int>> *v, int V) {
	for (int i = 0; i < V; i++) {
		cout << i << ":";
		for (auto el : v[i]) {
			cout << "(" << el.first << "," << el.second << ") -> ";
		}
		cout << endl;
	}
}

int minKey(int key[], bool mstSet[], int V){
	int min = INF, min_index;

	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}
void constructMST(int parent[], int **graph, vector<pair<int,int>> *adjList,int V)
{
    for (int i = 1; i < V; i++) {
        adjList[parent[i]].push_back(make_pair(i, graph[i][parent[i]]));
        adjList[i].push_back(make_pair(parent[i], graph[i][parent[i]]));
    }
}
vector<pair<int,int>> *primMST(int **graph, int V){
    vector<pair<int, int>>* adjList = new vector<pair<int, int>>[V];  
    int *parent = new int[V]; 
    int *key = new int[V]; 
    bool *mstSet = new bool[V];

    for (int i = 0; i < V; i++)
        key[i] = INF, mstSet[i] = false;
  
    key[0] = 0;
    parent[0] = -1;   
 
    for (int count = 0; count < V - 1; count++){
        int u = minKey(key, mstSet,V);

        mstSet[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
    constructMST(parent, graph,adjList,V);
    return adjList;
}
//dijsktra

typedef pair<int, int> iPair; 
int shortestPath(vector<pair<int,int> > adj[], int V, int src,int ll)  { 
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;  
    vector<int> dist(V, INF); 

    pq.push(make_pair(0, src)); 
    dist[src] = 0; 
  
    while (!pq.empty()){ 
        int u = pq.top().second; 
        pq.pop(); 
  
        for (auto x : adj[u]) { 
            int v = x.first; 
            int weight = x.second; 
 
            if (dist[v] > dist[u] + weight){ 
                dist[v] = dist[u] + weight; 
                pq.push(make_pair(dist[v], v)); 
            } 
        } 
    } 
    //cout << "dist: " << src << " to " << ll << " -> " << dist[ll] << endl;
    return dist[ll]; 
} 
#endif
