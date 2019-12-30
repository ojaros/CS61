#include <iostream>
#include <vector>
#include "event.h"
#include "pq.h"
using std::cout;
using std::endl;

class randomInteger{
public:
  unsigned int operator() (unsigned int);
} randomizer;

unsigned int randomInteger::operator() (unsigned int max)
{
  //rand return random random
  //convert to unsigned to make pos
  //take remainder to put in range
  unsigned int rval = rand();
  return rval % max;
}

unsigned int randBetween(int low, int high){
  return low + randomizer(high - low);
}

class SoftwareGurusBar{
public:
  //try with 50, then 40, 60... to determine optimal profit
  SoftwareGurusBar() : freeChairs(50), profit(0.0){

  }
  bool canSeat(unsigned int numberOfPeople);
  void order(unsigned int beerType);
  void leave(unsigned int numberOfPeople);

  unsigned int freeChairs;
  double profit;
};
SoftwareGurusBar theBar;
SimulationFramework theSimulation;


bool SoftwareGurusBar::canSeat(unsigned int numberOfPeople){
  // if room, seat
  cout << "Time: " << theSimulation.currentTime;
  cout << " Group of " << numberOfPeople << " customers arrives";
  if (numberOfPeople < freeChairs){
    cout << " Group is seated" << endl;
    freeChairs -= numberOfPeople;
    return true;
  }
  else {
    cout << " No room, group leaves" << endl;
    return false;
  }
}

void SoftwareGurusBar::order(unsigned int beerType){
  //serve beer
  cout << "Time: " << theSimulation.currentTime;
  cout << " serviced order for " << beerType << endl;
  //update profit based on this beerType
  if (beerType == 1) {
    profit += 2.0;
    cout << "Profit of $2" << endl;
  }
  else if (beerType == 2){
    profit += 3.0;
    cout << "Profit of $3" << endl;
  }
  else if (beerType == 3){
    profit += 4.0;
    cout << "Profit of $4" << endl;
  }
}

void SoftwareGurusBar::leave(unsigned int numberOfPeople){
  //people leave, free up chairs
  cout << "Time: " << theSimulation.currentTime;
  cout << " group of size " << numberOfPeople << " leaves" << endl;
  freeChairs += numberOfPeople;
}





class LeaveEvent : public Event {
public:
  LeaveEvent(unsigned int time, unsigned int gs) : Event(time), groupSize(gs){

  }
  virtual void processEvent(){
    theBar.leave(groupSize);
  }
protected:
  unsigned int groupSize;
};





class OrderEvent : public Event {
public:
  OrderEvent(unsigned int time, unsigned int gs) : Event(time), groupSize(gs) {

  }
  virtual void processEvent();
protected:
  unsigned int groupSize;
};

void OrderEvent::processEvent(){
  vector<unsigned int> vect;
  vect.push_back(15);
  vect.push_back(60);
  vect.push_back(25);
  //
  //each member orders beer (type 1, 2, 3)
  for (int i = 0; i < groupSize; i++){
    int p = theSimulation.weightedProbability(vect);
    theBar.order(p);
    //theBar.order(randBetween(1,3));
  }
  int t = theSimulation.currentTime + randBetween(15,35);
  //schedule LeaveEvent for group
  theSimulation.scheduleEvent(new LeaveEvent(t, groupSize));
}



class ArriveEvent : public Event{
public:
  ArriveEvent(unsigned int time, unsigned int gs) : Event(time), groupSize(gs) {

  }
  virtual void processEvent();

protected:
  unsigned int groupSize;
};


void ArriveEvent::processEvent(){
  if (theBar.canSeat(groupSize)){
    //place order within 2 and 10 min
    theSimulation.scheduleEvent(new OrderEvent(theSimulation.currentTime + randBetween(2,10), groupSize));
  }
}


class ReorderEvent: public Event{
public:
  ReorderEvent(unsigned int time, unsigned int gs) : Event(time), groupSize(gs){

  }
  virtual void processEvent();

protected:
  unsigned int groupSize;
};

void ReorderEvent::processEvent(){
  //might need to add more
  theSimulation.scheduleEvent(new OrderEvent(theSimulation.currentTime, groupSize));
}










int main(){
  // load priority queue with initial arrive events then run simulation
  unsigned int t = 0;

  //load 4 hours (240 mins) of Arrive Events
  while (t < 240){
    //new group every 2-5 mins
    t += randBetween(2,5);

    //group size ranges from 1 to 5
    theSimulation.scheduleEvent(new ArriveEvent(t, randBetween(1,5)));
  }

  //then run simulation and print profit
  theSimulation.run();
  cout << "Total profits " << theBar.profit << endl;
}
