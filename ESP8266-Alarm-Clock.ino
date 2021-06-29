#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "EEPROMAnything.h"
#include "get_time.h"
#include "OTA.h"
#include <stdio.h>
#include <stdint.h>
#include "web_portal.h"

#define daylightSavings true

#if defined daylightSavings
  #define timeZone 12
#else
  #define timeZone 13
#endif

#define TenSecs 10000000
#define OneMin 60000000
#define TenMins 600000000
#define lightOutput 4 //D2 = GPIO4
#define lightSwInput 5 //D1 = GPIO5

int timer;
int alarmTriggerTime;
int checkDayTimer;
struct CurrentTime Current;
bool AlarmActive;
struct AlarmDataStruct AlarmData;
int pollFrequency = TenSecs;
int dayofWeek;
int WiFiTimer;


void setup() {

  Serial.begin(115200);
  Serial.println("Booting");
  EEPROM.begin(512);
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  pinMode(lightOutput, OUTPUT);  //Initialise the output for the light
  pinMode(lightSwInput,INPUT_PULLUP); //Initialise the input for the light switch

  bool response;
  response = wm.autoConnect("AutoConnectAP"); // anonymous ap
  if(!response) {
      Serial.println("Failed to connect");
      // ESP.restart();
  } 
  else {
      //if you get here you have connected to the WiFi    
      Serial.println("Lets Go");
  }

  
  start_server();
  SetupOTA();
  setup_time(timeZone);
  Current = Current_Time();
  dayofWeek = GetDayofWeek();

  EEPROM_readAnything(100, AlarmData);
  Serial.print("Alarm set for ");
  Serial.print(AlarmData.Hour[dayofWeek]);
  Serial.print(":");
  Serial.println(AlarmData.Minute[dayofWeek]);
  timer = micros();
  WiFiTimer = timer;
}


void loop() {
  
  ArduinoOTA.handle();
  handle_client();

   if((micros() - WiFiTimer) > OneMin) // check if wifi connection lost and if so try to reconnect
   {
      if(WiFi.status() != WL_CONNECTED)
         {
            ESP.restart(); //try to reconnect rather than resetting
         }
      WiFiTimer = micros();
   }

  //update current hour
  if ((micros() - timer) > pollFrequency)
  {
    Current = Current_Time();
    timer = micros();
    if (abs(AlarmData.Hour[dayofWeek] - Current.Hour) < 2) //if alarm less than 2 hours away
    {
      pollFrequency = TenSecs;
      Serial.println("alarm is soon checking time every 10 secs");
    }
    else
    {
      pollFrequency = OneMin;
      Serial.println("alarm is ages away checking time every minute");
    }
  }


  if(AlarmActive)
  {
    if ((micros() - alarmTriggerTime) > TenMins)
    {
      AlarmActive = false; //if alarm active for 10mins and no one switches it off then do it auto
    }
  }


  if ((micros() - checkDayTimer) > TenMins)
  {
    dayofWeek = GetDayofWeek();
    if (new_day(dayofWeek))
    {
      EEPROM_readAnything(100, AlarmData);
      Serial.println("It's a new day, re-enabling today's alarm");
    }
    checkDayTimer = micros();
  }


  if (AlarmData.AlarmOn[dayofWeek])
  {
    if (!AlarmActive)//do not enter this routine if alarm already active
    {
      if (Current.Hour == AlarmData.Hour[dayofWeek])
      {
        if(Current.Minute == AlarmData.Minute[dayofWeek])
        {
          AlarmActive = true;
          Serial.println("Its time for your alarm!");
          TurnLightOn();
        }
      }
    }
  }
  
  
  if (!digitalRead(lightSwInput)) //if switch closed
  {
    if (AlarmActive)
    {
      AlarmActive = false;
      AlarmData.AlarmOn[dayofWeek] = false;
     Serial.println("You woke up. good work");
    }
    else
    {
      TurnLightOn();
    }
  
  }
  else
  {
    if(!AlarmActive)
    {
      TurnLightOff();
    }
  }

  
}


void TurnLightOff() {
  if (!digitalRead(lightOutput))
  {
  digitalWrite(lightOutput, HIGH);  // Turn the Light off
  Serial.println("Turning Light off");
  }
}


void TurnLightOn() {
  if (digitalRead(lightOutput))
  {
  digitalWrite(lightOutput, LOW);   // Turn the Light on
  Serial.println("Turning Light on");
  }
}
