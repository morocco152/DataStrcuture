#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include "lib.hpp"

#define INF 999999
using namespace std;
int weight{0};
int wnode{1};
int _w_dij{0};
void dfs(int start, bool *visited, vector<pair<int,int>> *adjList, int V, vector<int> &v){
  if(visited[start])return;
  visited[start] = true;
  v.push_back(start);
  for(auto u : adjList[start]){
    dfs(u.first, visited, adjList, V, v);
    weight += u.second;
    wnode++;
  }
}

int main(){
    int V = 1053;
    int** adj = new int* [V];
    for (int i = 0; i < V; i++) {
        adj[i] = new int[V];
        for (int j = 0; j < V; ++j) {
            if (i == j)
                adj[i][j] = 0;
            else
                adj[i][j] = INF;
        }
    }
    vector<pair<int,int>> *adjlist = new vector<pair<int,int>>[V];
    //printMatrix(adj, V);
    ifstream iFile{ "entrada.txt", ios::in};
    if (!iFile) {
        cout << "No se pudo abrir el arrchivo" << endl;
        return 1;
    }
    int nn,na,start,u, v, c;
    iFile >> nn;
    iFile >> na;
    iFile >> start;
    while (iFile >> u >> v >> c) {
        adj[u-1][v-1] = adj[v-1][u-1] = c;
        adjlist[u-1].push_back({v-1,c});
        adjlist[v-1].push_back({u-1,c});
    }
    iFile.close();
    //cout << endl;
    //printMatrix(adj, V);
    //cout << endl;
    //printList(adjlist, V);
    //cout << endl;
    //cout << "#Nodos: " << nn << endl;
    //cout << "#Aristas: " << na << endl;
    //cout << "#Start_node: " << start << endl;
    //cout << endl;
    vector<pair<int,int>> *mst = primMST(adj,V);
    printList(mst,V);
    cout << "GENERADO:" << endl;
    //dijkstra
    shortestPath(mst,V,721,711); 
    //end dijkstra

    vector<int> dfsT;
    bool *visited = new bool [V]; //v
    for(int i = 0; i<V; i++)
      visited[i] = false;
    dfs(start-1,visited,mst, V, dfsT);

    //cout << "Peso:" << weight << endl;
    //cout << "#nodos_visited: " << wnode << endl;

    //salida
    //vector<int> a;
    ofstream filewriter("salida.txt");
        
    filewriter << weight << endl; 
    filewriter << wnode << endl;
    filewriter << start << endl;

    for(auto it = dfsT.begin(); it != dfsT.end(); ++it){
      if(it == (dfsT.end() - 1)){
        filewriter << *it +1<< endl;
        //a.push_back(*it);
      }
      else{
        filewriter << *it +1<< endl;
        //a.push_back(*it);
      }
    }
      filewriter << start << endl;
      cout << "Peso:" << weight << endl;
      cout << "#nodos_visited: " << wnode << endl;
    //a.push_back(start-1);

    /*
    int cont{0};
    while (cont <= 1052) {
      filewriter << a[cont]+1 << " ";
      filewriter << a[++cont]+1 << endl;
      _w_dij += shortestPath(mst,V,a[cont],a[cont+1]);
    }
    _w_dij -= 2413;
    cout << "dist with dijs: " << _w_dij << endl;
    
    //salida
    */
    filewriter.close();
    //Destructor
    for(int i=0; i<V ; ++i){
      delete [] adj[i];
    }
    delete [] adjlist;
    delete [] visited;
    delete [] mst;
    return EXIT_SUCCESS;
}
