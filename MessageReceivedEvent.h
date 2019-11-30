#ifndef __MESSAGERECEIVEDEVENT__
#define __MESSAGERECEIVEDEVENT__

#include "Arduino.h"
#include "Event.h"

class MessageReceivedEvent : public Event {

  public:
    MessageReceivedEvent(int type, String message);
    String getMessage();

  private:
    String message;
};


#endif
