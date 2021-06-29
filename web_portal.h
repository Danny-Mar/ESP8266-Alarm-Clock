#ifndef WEB_PORTAL_H
#define WEB_PORTAL_H

#include <ESP8266WebServer.h>
#include "EEPROMAnything.h"


struct AlarmDataStruct {

int Hour[7];
int Minute[7];
bool AlarmOn[7];
  
};



void start_server();

void handleRoot();

void handle_client();

void handleSet();


#endif /* WEB_PORTAL_H */
