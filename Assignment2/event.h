/*
Framework for the simulation, includes SimulationFramework class and Event class
Priority queue elements will be inserted here
Will compare events based on their priority
*/
#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <queue>
#include <vector>
#include "pq.h"
using std::vector;


class Event{
public:
  //constructor requires time of event
  Event(unsigned int t) : time(t){

  }
  //time is public
  unsigned int time;
  //execute event
  virtual void processEvent(){

  }
};

class eventComparison {
public:
  bool operator() (Event *left, Event *right){
    return left->time > right->time;
  }
};

class SimulationFramework{
public:
  SimulationFramework() : eventQueue(1000), currentTime(0){

  }
  void scheduleEvent(Event *newEvent){
    //insert newEvent into eventQueue(PQ)
    //based on MinHeap using newEvents time
    eventQueue.insert(newEvent);
  }
  void run();
  int weightedProbability(vector<unsigned int> prob);
  unsigned int currentTime;

protected:
  MinPQ <Event *, eventComparison> eventQueue;
};

void SimulationFramework::run() {
  //execute until event queue empty
  while (! eventQueue.empty()){
    //copy and remove min-priority element (min time) from eventque
    Event *nextEvent = eventQueue.peak();
    
    eventQueue.delMin();

    //update simulations current time
    currentTime = nextEvent->time;

    //process nextEvent
    nextEvent->processEvent();

    //cleanup nextEvent object
    delete nextEvent;
  }
}

int SimulationFramework::weightedProbability(vector<unsigned int> prob){
  int sum = 0;
  for (int i = 0; i < 3; i++){
    sum += prob[i];
  }
  int num = rand() % sum + 1;
  if (num < prob[0]){
    return 1;
  }
  else if(num < prob[1]){
    return 2;
  }
  else {
    return 3;
  }
}


#endif
