#ifndef PROJECT_HPP
#define PROJECT_HPP
#include <string>
#include <iostream>
using namespace std;

struct CountyNode
{
string name;
int fireSeverity;
int neighboringCounties;
};

class PriorityQueue
{
public:
PriorityQueue(int queueSize);
~PriorityQueue();
void enqueue (string _name, int _fireSeverity, int _neighboringCounties);
void dequeue();
string peekName();
int peekFireSeverity();
int peekNeighboringCounties();
bool isFull();
bool isEmpty();

private:
void repairUpward(int nodeIndex);
void repairDownward(int nodeIndex);
CountyNode* priorityQueue;
int currentQueueSize;
int maxQueueSize;
};
#endif

PriorityQueue::PriorityQueue(int queueSize){
  maxQueueSize = queueSize;
  currentQueueSize = 0;
  priorityQueue = new CountyNode[maxQueueSize];
}

PriorityQueue::~PriorityQueue(){
  //destructor
}

void PriorityQueue::enqueue(string _name, int _fireSeverity, int _neighboringCounties){
  CountyNode newNode;
  newNode.name = _name;
  newNode.fireSeverity = _fireSeverity;
  newNode.neighboringCounties = _neighboringCounties;
  priorityQueue[currentQueueSize] = newNode;
  int index = currentQueueSize;
  currentQueueSize++;
  repairUpward(index);
}

void PriorityQueue::dequeue(){
  repairDownward(0);
  currentQueueSize--;
}

string PriorityQueue::peekName(){
  string peeking = priorityQueue[0].name;
  return peeking;
}

int PriorityQueue::peekFireSeverity(){
  int peeking = priorityQueue[0].fireSeverity;
  return peeking;
}

int PriorityQueue::peekNeighboringCounties(){
  int peeking = priorityQueue[0].neighboringCounties;
  return peeking;
}

bool PriorityQueue::isFull(){
  if(currentQueueSize == maxQueueSize){
    return true;
  }
  else{
    return false;
  }
}

bool PriorityQueue::isEmpty(){
  if(currentQueueSize==0){
    return true;
  }
  else{
    return false;
  }
}

void PriorityQueue::repairDownward(int nodeIndex){
  for(int i = nodeIndex; i<currentQueueSize; i++){
    priorityQueue[i]=priorityQueue[i+1];
  }
  for(int j = 0; j < currentQueueSize; j++){
    if(priorityQueue[j].neighboringCounties > priorityQueue[j+1].neighboringCounties && priorityQueue[j].fireSeverity==priorityQueue[j+1].fireSeverity){
        CountyNode swap = priorityQueue[j];
        priorityQueue[j]=priorityQueue[j+1];
        priorityQueue[j+1]=swap;
    }
  }
}

void PriorityQueue::repairUpward(int nodeIndex){
  if(nodeIndex == 1){
    return;
  }
  CountyNode parent = priorityQueue[nodeIndex-1];
  if(priorityQueue[nodeIndex].fireSeverity < parent.fireSeverity){
    return;
  }
  if(priorityQueue[nodeIndex].fireSeverity == parent.fireSeverity){
    if(priorityQueue[nodeIndex].neighboringCounties < parent.neighboringCounties){
      CountyNode temp = priorityQueue[nodeIndex];
      priorityQueue[nodeIndex] = parent;
      priorityQueue[nodeIndex-1] = temp;
      repairUpward(nodeIndex-1);
    }
    else{
      return;
    }
  }
  if(priorityQueue[nodeIndex].fireSeverity > parent.fireSeverity){
    CountyNode temp = priorityQueue[nodeIndex];
    priorityQueue[nodeIndex] = parent;
    priorityQueue[nodeIndex-1] = temp;
    repairUpward(nodeIndex-1);
  }
}
