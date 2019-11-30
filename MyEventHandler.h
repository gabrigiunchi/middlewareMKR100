#ifndef __MYEVENTHANDLER__
#define __MYEVENTHANDLER__

#include "Event.h"
#include "EventHandler.h"
#include "WiFi101.h"

class MyEventHandler : public EventHandler {

  public: 
    MyEventHandler(WiFiClient* client);
    void notifyObserver(Event* e);


  private:
    WiFiClient* client;
  
};

#endif
