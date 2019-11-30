#include "Event.h"
#include "EventHandler.h"

bool EventHandler :: isTriggered(Event* e) {
  for(int i = 0; i < this->arraySize; i++) {
    if(this->observedEvents[i] == e->getType()) {
      return true;
    }
  }
  
  return false;
}

void EventHandler :: addObservedEvent(int type) {
  this->observedEvents[this->arraySize] = type;
  this->arraySize++;
}

