#ifndef __EVENT__
#define __EVENT__

/* 
 *  Evento generico identificato da un tipo
 */
class Event {
  public:
    Event(int type);
    int getType();
    
  private:
    int type;
};

#endif

