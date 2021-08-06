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
#include "ESP8266TimerInterrupt.h"
#include "restore_factory_settings.h"

#define timeZone 12

#define TenSecs 10000000
#define OneMin 60000000
#define TenMins 600000000
#define lightOutput 4 //D2 = GPIO4
#define lightSwInput 5 //D1 = GPIO5
#define TIMER_INTERVAL_MS	1000 

ESP8266Timer ITimer;

int timer;
int alarmTriggerTime;
struct CurrentTime Current;
bool AlarmActive;
struct AlarmDataStruct AlarmData;
int WiFiTimer;
char factory_settings_stored [3];
bool OneSecoundPassed;

void ICACHE_RAM_ATTR TimerHandler(void)
{
OneSecoundPassed = true;
}



void setup() {

  Serial.begin(115200);
  Serial.println("Booting");
  EEPROM.begin(512);
  EEPROM_readAnything(150, factory_settings_stored);
  if(memcmp(&factory_settings_stored,"YES",3) != 0)
  {
    restore_factory_settings();
  }
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

  EEPROM_readAnything(100, AlarmData);
  Serial.print("Alarm set for ");
  Serial.print(AlarmData.Hour[Current.Day]);
  Serial.print(":");
  Serial.println(AlarmData.Minute[Current.Day]);
  timer = micros();
  WiFiTimer = timer;
  
  // Interval in microsecs
  if (ITimer.attachInterruptInterval(TIMER_INTERVAL_MS * 1000, TimerHandler))
  {
  Serial.println("Starting  ITimer OK, millis() = " + String(millis()));
  }
  else
  {
  Serial.println("Can't set ITimer correctly. Select another freq. or interval");
  }
}


void loop() {
  
  ArduinoOTA.handle();
  handle_client();

   if((micros() - WiFiTimer) > TenMins) // check if wifi connection lost and if so try to reconnect
   {
      if(WiFi.status() != WL_CONNECTED)
         {
            ESP.restart(); //try to reconnect rather than resetting
         }
      WiFiTimer = micros();
   }

   if(OneSecoundPassed)
   {
    updateLocalTime();
    OneSecoundPassed = false;
   }

  //update current hour from NTP server
  if ((micros() - timer) > TenMins)
  {
    Current = Current_Time();
    timer = micros();
  }


  if(AlarmActive)
  {
    if ((micros() - alarmTriggerTime) > TenMins)
    {
      AlarmActive = false; //if alarm active for 10mins and no one switches it off then do it auto
    }
  }


  if (AlarmData.AlarmOn[Current.Day])
  {
    if (!AlarmActive)//do not enter this routine if alarm already active
    {
      if (Current.Hour == AlarmData.Hour[Current.Day])
      {
        if(Current.Minute == AlarmData.Minute[Current.Day])
        {
          if(Current.Second > 0 && Current.Second < 3)
          {
            AlarmActive = true;
            alarmTriggerTime = micros();
            Serial.println("Its time for your alarm!");
            TurnLightOn();
          }
        }
      }
    }
  }
  
  
  if (!digitalRead(lightSwInput)) //if switch closed
  {
    if (AlarmActive)
    {
      AlarmActive = false;
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

void updateLocalTime () {
Current.Second++;
if (Current.Second >= 60)
{
  Current.Second = 0;
  Current.Minute++;
  if(Current.Minute >= 60)
  {
    Current.Minute = 0;
    Current.Hour++;
    if(Current.Hour >= 24)
    {
      Current.Hour = 0;
      Current.Day++;
      if(Current.Day >= 7)
      {
        Current.Day = 0;
      }
    }
  }
}
char tempTime[6];
if(Current.Minute<10 && Current.Second<10)
{
  sprintf(tempTime,"0%d:0%d", Current.Minute,Current.Second);
}
else if(Current.Minute<10)
{
  sprintf(tempTime,"0%d:%d", Current.Minute,Current.Second);
}
else if(Current.Second<10)
{
  sprintf(tempTime,"%d:0%d", Current.Minute,Current.Second);
}
else
{
  sprintf(tempTime,"%d:%d", Current.Minute,Current.Second);
}
Serial.println(tempTime);
}
