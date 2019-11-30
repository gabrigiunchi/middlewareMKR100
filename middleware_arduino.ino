#include "SPI.h"
#include "WiFi101.h"
#include "EventsCode.h"
#include "EventHandlerManager.h"
#include "MessageReceivedEvent.h"
#include "MyEventHandler.h"

#define RETRY_TIME 5000

#define ssid "yourNetwork"
#define password "secretPassword"
#define serverIp "ipServer"
#define serverPort 1234

String message = "";
int status = WL_IDLE_STATUS; // stato del wi-fi
WiFiClient* client;

void setup() {
  Serial.begin(9600);
  message.reserve(40);

  // Shield wifi non presente, non proseguo
  if(WiFi.status() == WL_NO_SHIELD) {
    while (true) {}
  }

  // Tento di connettermi al modem
  while(status != WL_CONNECTED) {
    status = WiFi.begin(ssid, password);
    delay(RETRY_TIME);
  }

  // Tento di connettermi al server
  while(!client->connect(serverIp, serverPort)) {
    delay(RETRY_TIME);
  } 

  addEventHandler(new MyEventHandler(client));
}

void loop() {
  mainEventLoop();
  
  if(client->available()) {
    message = client->readStringUntil('\n');
    dispatchEvent(new MessageReceivedEvent(NET_MESSAGE_RECEIVED, message));
  }
}

// Invocato automaticamente se sono presenti dati sulla seriale
void serialEvent() {
  message = Serial.readStringUntil('\n');
  dispatchEvent(new MessageReceivedEvent(SERIAL_MESSAGE_RECEIVED, message));
}

