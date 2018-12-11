#include <iostream>
#include <list>
using namespace std;

//Tristan Hanna

class Graph
{
  private:
    int V;
    list<string> *adj;
  public:
    Graph(int V);
    void addEdge(int v, string w);
    int getNumEdges(int v);
};

Graph::Graph(int V)
{
  this->V = V;
  adj = new list<string>[V];
}

void Graph::addEdge(int v, string w)
{
  adj[v].push_back(w);
}

int Graph::getNumEdges(int v){
  int numEdges=0;
  list<string>::iterator i;
  for(i = adj[v].begin(); i != adj[v].end(); i++){
    numEdges++;
  }
  return numEdges;
}
