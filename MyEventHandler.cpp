#include "MyEventHandler.h"
#include "EventsCode.h"
#include "MessageReceivedEvent.h"

MyEventHandler :: MyEventHandler(WiFiClient* client) : EventHandler() {
  this->addObservedEvent(SERIAL_MESSAGE_RECEIVED);
  this->addObservedEvent(NET_MESSAGE_RECEIVED);
 
  this->client = client;
}

void MyEventHandler :: notifyObserver(Event* e) {
  int code = e->getType();
  String temp = "";

  /*
   * Due possibili casi
   * 
   * - Quando ricevo un messaggio sulla seriale lo reindirizzo al server
   * - Quando ricevo un messaggio dal server lo reindirizzo sulla seriale
   */
  switch(code) {
    case NET_MESSAGE_RECEIVED: 
      temp = ((MessageReceivedEvent*)e)->getMessage();
      Serial.print(temp); 
      break;
      
    case SERIAL_MESSAGE_RECEIVED : 
      temp = ((MessageReceivedEvent*)e)->getMessage();
      this->client->print(temp); 
      break;
      
    default: break;
  }
}

