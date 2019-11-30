#include "EventHandlerManager.h"
#include "EventHandler.h"
#include "Event.h"

EventHandlerManager* EventHandlerManager::instance = new EventHandlerManager();

EventHandlerManager* EventHandlerManager::getInstance(){
  return instance;
}

EventHandlerManager::EventHandlerManager(){
  nEventHandlers = 0;  
}
  
bool EventHandlerManager::addEventHandler(EventHandler* eventHandler){
  if (nEventHandlers < MAX_HANDLERS){
    eventHandlers[nEventHandlers] = eventHandler;
    nEventHandlers++;
    return true;
  } else {
    return false;  
  }
}
  
void EventHandlerManager::dispatchEvent(Event* ev){
  cli();
  eventQueue.enqueue(ev);
  sei();
}

void EventHandlerManager::mainEventLoop(){
  bool isEmpty = true;
  
  cli();
  isEmpty = eventQueue.isEmpty();
  sei();

  if(!isEmpty) {
    cli();
    Event* ev = eventQueue.dequeue();
    sei();

    // dispatch event 
    for (int i = 0; i < nEventHandlers; i++){
      if (eventHandlers[i]->isTriggered(ev)){
        eventHandlers[i]->notifyObserver(ev);
      }
    }    
    
    delete ev;
  }
}

void EventHandlerManager::clearEvents(){
  while(!eventQueue.isEmpty()){
    eventQueue.dequeue();
  }
}

/********************* Global **************/
bool addEventHandler(EventHandler* e){
  return EventHandlerManager::getInstance()->addEventHandler(e);
}  

void dispatchEvent(Event* ev){
  return EventHandlerManager::getInstance()->dispatchEvent(ev);
}

void mainEventLoop(){
  EventHandlerManager::getInstance()->mainEventLoop();
}

void clearEvents(){
  EventHandlerManager::getInstance()->clearEvents();
}
