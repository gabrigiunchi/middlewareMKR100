#ifndef __EVENTHANDLER__
#define __EVENTHANDLER__

#include "Event.h"

#define MAX_OBSERVED_EVENTS 10


class EventHandler {

  public:
    virtual void notifyObserver(Event* e) = 0;
    bool isTriggered(Event* e);
    void addObservedEvent(int type);

  private:
    int observedEvents[MAX_OBSERVED_EVENTS];
    int arraySize = 0;

};

#endif
