#include "Project.hpp"
#include "graph.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main(){
  cout << "Welcome to the Fire Department!" <<endl;
  cout << "First, load your state's counties' neighboring counties information." <<endl;
  cout << "Then, load current wildfire information. Before all this, the program needs some information." <<endl;
  int total=0;
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
        i++;
        while(getline(ss, item, ',')){
          counties.addEdge(i, item);
        }
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
              queue.enqueue(name, severity, numNeighboringCounties);
              cout << "done" <<endl;
            }
          }
        }
        else{
          cout << "Priority Queue full. Send in reinforcments!" <<endl;
        }
      }
    }
    else if(answer=="3"){
      cout << "Enter County Name:" <<endl;
      string newName;
      getline(cin, newName);
      cout << "Enter Fire Severity:" <<endl;
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
        queue.enqueue(newName, newSeverity, numCounties);
        cout << "Fire in " << newName << " added to queue. Fire has severity of " << newSeverity << " and has " << numCounties << " neighboring counties."<<endl;
      }
      else{
        cout << "Priority Queue full. Send in reinforcements!" <<endl;
      }
    }
    else if(answer=="4"){
      if(queue.isEmpty()==false){
        string printName = queue.peekName();
        int printSeverity = queue.peekFireSeverity();
        int printCounties = queue.peekNeighboringCounties();
        cout << "County Name: " << printName <<endl;
        cout << "Fire Severity: " << printSeverity <<endl;
        cout << "Neighboring Counties: " << printCounties <<endl;
      }
      else{
        cout << "Queue empty." <<endl;
      }
    }
    else if(answer=="5"){
      if(queue.isEmpty()==false){
        string countyName = queue.peekName();
        queue.dequeue();
        total = total + 1;
        cout << "County Fought: " << countyName <<  " - Total Fires fought: " << total <<endl;
      }
      else{
        cout << "Queue empty." <<endl;
      }
    }
  }
  cout << "Goodbye!" <<endl;
}
