#ifndef PROJECT_HPP
#define PROJECT_HPP
#include <string>
#include <iostream>
using namespace std;

struct CountyNode
{
string name;
int days;
int severity;
int neighboringCounties;
};

class PriorityQueue
{
public:
PriorityQueue(int queueSize);
~PriorityQueue();
void enqueue (string _name, int _days, int _severity, int _neighboringCounties);
void dequeue();
string peekName();
int peekSeverity();
int peekDays();
int peekNeighboringCounties();
bool isFull();
bool isEmpty();
void dayOver();

private:
void repairUpward(int nodeIndex);
void repairDownward(int nodeIndex);
CountyNode* priorityQueue;
int currentQueueSize;
int maxQueueSize;
};
#endif

void PriorityQueue::dayOver(){
  for(int i = 0; i < currentQueueSize; i++){
    priorityQueue[i].days++;
    if(priorityQueue[i].days%2==0){
      if(priorityQueue[i].severity<10){
        priorityQueue[i].severity++;
      }
    }
  }
}

PriorityQueue::PriorityQueue(int queueSize){
  maxQueueSize = queueSize;
  currentQueueSize = 0;
  priorityQueue = new CountyNode[maxQueueSize];
}

PriorityQueue::~PriorityQueue(){
  //destructor
}

void PriorityQueue::enqueue(string _name, int _days, int _severity, int _neighboringCounties){
  CountyNode newNode;
  newNode.name = _name;
  newNode.days = _days;
  newNode.neighboringCounties = _neighboringCounties;
  newNode.severity = _severity;
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

int PriorityQueue::peekSeverity(){
  int peeking = priorityQueue[0].severity;
  return peeking;
}

int PriorityQueue::peekDays(){
  int peeking = priorityQueue[0].days;
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
    if(priorityQueue[j].neighboringCounties > priorityQueue[j+1].neighboringCounties && priorityQueue[j].severity==priorityQueue[j+1].severity){
        CountyNode swap = priorityQueue[j];
        priorityQueue[j]=priorityQueue[j+1];
        priorityQueue[j+1]=swap;
    }
  }
}

void PriorityQueue::repairUpward(int nodeIndex){
  if(nodeIndex == 0){
    return;
  }
  CountyNode parent = priorityQueue[nodeIndex-1];
  if(priorityQueue[nodeIndex].severity < parent.severity){
    return;
  }
  if(priorityQueue[nodeIndex].severity == parent.severity){
    if(priorityQueue[nodeIndex].neighboringCounties > parent.neighboringCounties){
      CountyNode temp = priorityQueue[nodeIndex];
      priorityQueue[nodeIndex] = parent;
      priorityQueue[nodeIndex-1] = temp;
      repairUpward(nodeIndex-1);
    }
    else{
      return;
    }
  }
  if(priorityQueue[nodeIndex].severity > parent.severity){
    CountyNode temp = priorityQueue[nodeIndex];
    priorityQueue[nodeIndex] = parent;
    priorityQueue[nodeIndex-1] = temp;
    repairUpward(nodeIndex-1);
  }
}
