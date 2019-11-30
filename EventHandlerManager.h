#ifndef __HANDLERMANAGER__
#define __HANDLERMANAGER__

#include "Arduino.h"
#include "Event.h"
#include "EventHandler.h"

#define MAX_HANDLERS 20 // numero massimo di handlers gestiti
#define MAX_EVQUEUE_SIZE 50 // lunghezza della coda di eventi gestiti

// Classe utilizzata per la gestione della coda di eventi (politica FIFO)
class EventQueue{
  public:
    EventQueue(){
      head = tail = 0; 
    }
    bool isEmpty() {
      return head == tail; 
    }
    void enqueue(Event* ev){
      queue[tail] = ev;
      tail = (tail+1) % MAX_EVQUEUE_SIZE;
    }
    Event* dequeue(){
      if (isEmpty()){
        return 0;
      } else {
        Event* pev = queue[head];
        head = (head+1) % MAX_EVQUEUE_SIZE;
        return pev; 
      }
    }
  
  private:
    Event* queue[MAX_EVQUEUE_SIZE];
    int head, tail; 
};

// classe EventHandlerManager che gestisce gli event handler e il dispatch di eventi
class EventHandlerManager {
  public:
    static EventHandlerManager* getInstance();  
    bool addEventHandler(EventHandler* eventHandler);  
    void dispatchEvent(Event* ev);
    void mainEventLoop();
    void clearEvents();
  
  private:
    EventHandlerManager();    
    EventQueue eventQueue;
    int nEventHandlers;
    EventHandler* eventHandlers[MAX_HANDLERS];
    
    static EventHandlerManager* instance;
};

/* ------------------------ Global  ------------------------ */

bool addEventHandler(EventHandler* e);
void dispatchEvent(Event* ev);
void mainEventLoop();
void clearEvents();

#endif



