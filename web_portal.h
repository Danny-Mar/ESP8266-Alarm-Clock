#ifndef WEB_PORTAL_H
#define WEB_PORTAL_H

#include <ESP8266WebServer.h>
#include "EEPROMAnything.h"


struct AlarmDataStruct {

uint8_t Hour[7];
uint8_t Minute[7];
uint8_t AlarmOn[7];
  
};



void start_server();

void handleRoot();

void handle_client();

void handleSet();


#endif /* WEB_PORTAL_H */
