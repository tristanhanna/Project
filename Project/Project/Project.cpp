#include "Project.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
using namespace std;

class Graph
{
  private:
    int V;
    list<string> *adj;
  public:
    Graph(int V);
    void addEdge(int v, string w);
    int getNumEdges(int v);
    void getAdjacents(int v, string arr[]);
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

void Graph::getAdjacents(int v, string arr[]){
  int x = 0;
  list<string>::iterator i;
  for(i = adj[v].begin(); i != adj[v].end(); i++){
    arr[x] = *i;
    x++;
  }
}

int main(){
  cout << "Welcome to the Wildfire Department!" <<endl;
  cout << "This program uses information from your state to determine which wildfire should have priority" <<endl;
  cout << "to be fought compared to other fires in the area. It does this by comparing the number of connecting" <<endl;
  cout << "counties and the days it has been an ongoing fire. If the fire does not get fought within three days" <<endl;
  cout << "then it will spread to the surrounding counties." <<endl;
  int total=0;
  int days=0;
  cout << "How many counties are in your state?:" <<endl;
  string s_count;
  getline(cin, s_count);
  int count = stoi(s_count);
  Graph counties(count);
  string countiesArray[count];
  cout << "How many fires can your department handle before reinforcements are needed?" <<endl;
  string s_size;
  getline(cin, s_size);
  int size=stoi(s_size);
  PriorityQueue queue(size);
  cout << "First, load your file of counties and their connecting counties." <<endl;
  cout << "Then, load your file with the current wildfires to the Priority Queue." <<endl;
  string answer="";
  while(answer!="6"){
    cout << "======Main Menu======" << endl;
    cout << "1. Get County Information from File" << endl;
    cout << "2. Get Fire Information from File" << endl;
    cout << "3. Add Fire to Priority Queue" << endl;
    cout << "4. Show Next Fire" << endl;
    cout << "5. Fight Next Fire" << endl;
    cout << "6. Quit" << endl;
    getline(cin, answer);
    if(answer=="1"){
      cout << "Enter filename:" <<endl;
      string file;
      getline(cin, file);
      ifstream inFile(file);
      string line="";
      int i = 0;
      while(getline(inFile, line)){
        stringstream ss;
        ss << line;
        string item;
        getline(ss, item, ',');
        string theCounty = item;
        countiesArray[i]=item;
        while(getline(ss, item, ',')){
          counties.addEdge(i, item);
        }
        i++;
      }
      cout << "Counties and their adjacents added!" <<endl;
    }
    else if(answer=="2"){
      cout << "Enter filename:" <<endl;
      string file;
      getline(cin, file);
      ifstream inFile(file);
      string line="";
      while(getline(inFile, line)){
        stringstream ss;
        ss << line;
        string item;
        getline(ss, item, ' ');
        string name = item;
        getline(ss, item, ' ');
        int severity = stoi(item);
        if(queue.isFull()==false){
          for(int j = 0; j < count; j++){
            if(countiesArray[j]==name){
              int numNeighboringCounties = counties.getNumEdges(j);
              queue.enqueue(name, 0, severity, numNeighboringCounties);
            }
          }
        }
        else{
          cout << "Priority Queue full. Send in reinforcments!" <<endl;
        }
      }
      cout << "Current Fires added!" <<endl;
    }
    else if(answer=="3"){
      cout << "Enter County Name:" <<endl;
      string newName;
      getline(cin, newName);
      cout << "Enter Severity:" <<endl;
      string sevty;
      getline(cin, sevty);
      int newSeverity = stoi(sevty);
      int numCounties;
      for(int x = 0; x < count; x++){
        if(countiesArray[x] == newName){
          numCounties = counties.getNumEdges(x);
        }
      }
      if(queue.isFull()==false){
        queue.enqueue(newName, 0, newSeverity, numCounties);
        cout << "Fire in " << newName << " added to queue. Fire has severity of " << newSeverity << " and " << numCounties << " neighboring counties."<<endl;
      }
      else{
        cout << "Priority Queue full. Send in reinforcements!" <<endl;
      }
    }
    else if(answer=="4"){
      if(queue.isEmpty()==false){
        string printName = queue.peekName();
        int printDays = queue.peekDays();
        int printCounties = queue.peekNeighboringCounties();
        int printSeverity = queue.peekSeverity();
        cout << "County Name : " << printName <<endl;
        cout << "Severity : " << printSeverity <<endl;
        cout << "Days : " << printDays <<endl;
        cout << "Neighboring Counties : " << printCounties <<endl;
      }
      else{
        cout << "Queue empty." <<endl;
      }
    }
    else if(answer=="5"){
      if(queue.isEmpty()==false){
        string countyName = queue.peekName();
        queue.dequeue();
        queue.dayOver();
        total = total + 1;
        cout << "County Fought: " << countyName <<  " - Total Fires fought: " << total <<endl;
        if(queue.peekSeverity()==10){
          int siize = queue.peekNeighboringCounties();
          string adjacents[siize];
          cout << "Oh no! The fire in " << queue.peekName() << " has reached extreme severity and has spread to the surrounding counties!" <<endl;
          for(int i = 0; i < count; i++){
            if(queue.peekName()==countiesArray[i]){
              counties.getAdjacents(i, adjacents);
            }
          }
          int numCounties;
          for(int j = 0; j < siize; j++){
            for(int x = 0; x < count; x++){
              if(countiesArray[x] == countyName){
                numCounties = counties.getNumEdges(x);
              }
            }
            queue.enqueue(adjacents[j], 0, 1, numCounties);
            cout << "Fire in " << adjacents[j] << " has been added to Priority Queue with severity of 1." <<endl;
          }
        }
      }
      else{
        cout << "Queue empty." <<endl;
      }
    }
  }
  cout << "Goodbye!" <<endl;
}
