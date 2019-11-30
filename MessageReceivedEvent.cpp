#include "MessageReceivedEvent.h"
#include "Arduino.h"

MessageReceivedEvent :: MessageReceivedEvent(int type, String message) : Event(type) {
  this->message = message;
}

String MessageReceivedEvent :: getMessage() {
  return this->message;
}

