#include "web_portal.h"

ESP8266WebServer server ( 80 );

const char* www_username = "admin";
const char* www_password = "admin";


void start_server(){
    server.on ("/", handleRoot);
    server.on ("/set", handleSet);
    
    server.begin();
}


void handle_client(){
server.handleClient();
}


void handleRoot()
{
    if (!server.authenticate(www_username, www_password)) {
      return server.requestAuthentication();
    }
  
  String MondayAlarmSetHTML;
  String TuesdayAlarmSetHTML;
  String WedAlarmSetHTML; 
  String ThursdayAlarmSetHTML;
  String FridayAlarmSetHTML;
  String SatAlarmSetHTML;
  String SundayAlarmSetHTML; 
  String Page;
  char tempTime[7][6];
  struct AlarmDataStruct AlarmSettings;

  EEPROM_readAnything(100,AlarmSettings);


  for(int i = 0; i <8; i++)
  {
      if(AlarmSettings.Hour[i]<10 && AlarmSettings.Minute[i]<10)
      {
        sprintf(tempTime[i],"0%d:0%d", AlarmSettings.Hour[i],AlarmSettings.Minute[i]);
      }
      else if(AlarmSettings.Hour[i]<10)
      {
        sprintf(tempTime[i],"0%d:%d", AlarmSettings.Hour[i],AlarmSettings.Minute[i]);
      }
      else if(AlarmSettings.Minute[i]<10)
      {
        sprintf(tempTime[i],"%d:0%d", AlarmSettings.Hour[i],AlarmSettings.Minute[i]);
      }
      else
      {
        sprintf(tempTime[i],"%d:%d", AlarmSettings.Hour[i],AlarmSettings.Minute[i]);
      }
  }
  tempTime[7][0] = '\0';


  
  if(AlarmSettings.AlarmOn[1]){
    MondayAlarmSetHTML = "<input type=\"radio\" name=\"MondayAlarmState\" value=\"D\" checked> ON"
                    "<input type=\"radio\" name=\"MondayAlarmState\" value=\"O\"> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"MondayAlarmValue\" id=\"MondayAlarmValue\" value='";
    MondayAlarmSetHTML += tempTime[1];
    MondayAlarmSetHTML += "' size=2 autofocus>";
                     
  }else{
    MondayAlarmSetHTML = "<input type=\"radio\" name=\"MondayAlarmState\" value=\"D\"> ON"
                    "<input type=\"radio\" name=\"MondayAlarmState\" value=\"O\" checked> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"MondayAlarmValue\" id=\"MondayAlarmValue\" value='";
    MondayAlarmSetHTML += tempTime[1];
    MondayAlarmSetHTML += "' size=2 autofocus>";                        
  } 
  
  if(AlarmSettings.AlarmOn[2]){
    TuesdayAlarmSetHTML = "<input type=\"radio\" name=\"TuesdayAlarmState\" value=\"D\" checked> ON"
                    "<input type=\"radio\" name=\"TuesdayAlarmState\" value=\"O\"> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"TuesdayAlarmValue\" id=\"TuesdayAlarmValue\" value='";
    TuesdayAlarmSetHTML += tempTime[2];
    TuesdayAlarmSetHTML += "' size=2 autofocus>";
                     
  }else{
    TuesdayAlarmSetHTML = "<input type=\"radio\" name=\"TuesdayAlarmState\" value=\"D\"> ON"
                    "<input type=\"radio\" name=\"TuesdayAlarmState\" value=\"O\" checked> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"TuesdayAlarmValue\" id=\"TuesdayAlarmValue\" value='";
    TuesdayAlarmSetHTML += tempTime[2];
    TuesdayAlarmSetHTML += "' size=2 autofocus>";                        
  } 
  

  if(AlarmSettings.AlarmOn[3]){
    WedAlarmSetHTML = "<input type=\"radio\" name=\"WedAlarmState\" value=\"D\" checked> ON"
                    "<input type=\"radio\" name=\"WedAlarmState\" value=\"O\"> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"WedAlarmValue\" id=\"WedAlarmValue\" value='";
    WedAlarmSetHTML += tempTime[3];
    WedAlarmSetHTML += "' size=2 autofocus>";
                     
  }else{
    WedAlarmSetHTML = "<input type=\"radio\" name=\"WedAlarmState\" value=\"D\"> ON"
                    "<input type=\"radio\" name=\"WedAlarmState\" value=\"O\" checked> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"WedAlarmValue\" id=\"WedAlarmValue\" value='";
    WedAlarmSetHTML += tempTime[3];
    WedAlarmSetHTML += "' size=2 autofocus>";                        
  }

  if(AlarmSettings.AlarmOn[4]){
    ThursdayAlarmSetHTML = "<input type=\"radio\" name=\"ThursAlarmState\" value=\"D\" checked> ON"
                    "<input type=\"radio\" name=\"ThursAlarmState\" value=\"O\"> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"ThursAlarmValue\" id=\"ThursAlarmValue\" value='";
    ThursdayAlarmSetHTML += tempTime[4];
    ThursdayAlarmSetHTML += "' size=2 autofocus>";
                     
  }else{
    ThursdayAlarmSetHTML = "<input type=\"radio\" name=\"ThursAlarmState\" value=\"D\"> ON"
                    "<input type=\"radio\" name=\"ThursAlarmState\" value=\"O\" checked> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"ThursAlarmValue\" id=\"ThursAlarmValue\" value='";
    ThursdayAlarmSetHTML += tempTime[4];
    ThursdayAlarmSetHTML += "' size=2 autofocus>";                        
  }

  if(AlarmSettings.AlarmOn[5]){
    FridayAlarmSetHTML = "<input type=\"radio\" name=\"FridayAlarmState\" value=\"D\" checked> ON"
                    "<input type=\"radio\" name=\"FridayAlarmState\" value=\"O\"> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"FridayAlarmValue\" id=\"FridayAlarmValue\" value='";
    FridayAlarmSetHTML += tempTime[5];
    FridayAlarmSetHTML += "' size=2 autofocus>";
                     
  }else{
    FridayAlarmSetHTML = "<input type=\"radio\" name=\"FridayAlarmState\" value=\"D\"> ON"
                    "<input type=\"radio\" name=\"FridayAlarmState\" value=\"O\" checked> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"FridayAlarmValue\" id=\"FridayAlarmValue\" value='";
    FridayAlarmSetHTML += tempTime[5];
    FridayAlarmSetHTML += "' size=2 autofocus>";                        
  }

    if(AlarmSettings.AlarmOn[6]){
    SatAlarmSetHTML = "<input type=\"radio\" name=\"SatAlarmState\" value=\"D\" checked> ON"
                    "<input type=\"radio\" name=\"SatAlarmState\" value=\"O\"> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"SatAlarmValue\" id=\"SatAlarmValue\" value='";
    SatAlarmSetHTML += tempTime[6];
    SatAlarmSetHTML += "' size=2 autofocus>";
                     
  }else{
    SatAlarmSetHTML = "<input type=\"radio\" name=\"SatAlarmState\" value=\"D\"> ON"
                    "<input type=\"radio\" name=\"SatAlarmState\" value=\"O\" checked> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"SatAlarmValue\" id=\"SatAlarmValue\" value='";
    SatAlarmSetHTML += tempTime[6];
    SatAlarmSetHTML += "' size=2 autofocus>";                        
  }

    if(AlarmSettings.AlarmOn[0]){
    SundayAlarmSetHTML = "<input type=\"radio\" name=\"SundayAlarmState\" value=\"D\" checked> ON"
                    "<input type=\"radio\" name=\"SundayAlarmState\" value=\"O\"> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"SundayAlarmValue\" id=\"SundayAlarmValue\" value='";
    SundayAlarmSetHTML += tempTime[0];
    SundayAlarmSetHTML += "' size=2 autofocus>";
                     
  }else{
    SundayAlarmSetHTML = "<input type=\"radio\" name=\"SundayAlarmState\" value=\"D\"> ON"
                    "<input type=\"radio\" name=\"SundayAlarmState\" value=\"O\" checked> OFF &nbsp &nbsp"
                    "<input type=\"text\" name=\"SundayAlarmValue\" id=\"SundayAlarmValue\" value='";
    SundayAlarmSetHTML += tempTime[0];
    SundayAlarmSetHTML += "' size=2 autofocus>";                        
  }

Page =  "<!DOCTYPE html>";
Page += "<html lang=\"en\">";
Page += "<head>";
Page += "<TITLE>Alarm Server</TITLE>";
Page += "<meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
Page += "</head>";
Page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>";
Page += "<style> .button { background-color: #4CAF50; border: on; color: white; padding: 6px 25px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer;}</style>";
Page += "<body>";
Page += "<h1>IoT Alarm Clock</h1>";
Page += "<h2>Please enter your next Alarm in format (05:45)</h2>";
Page += "<form id=\"Alarmform\">";
Page += "<fieldset>";
Page += "<legend>Monday Alarm</legend>";
Page +=   MondayAlarmSetHTML;
Page += "</fieldset>";
Page += "<fieldset>";
Page += "<legend>Tuesday Alarm</legend>";
Page +=   TuesdayAlarmSetHTML;
Page += "</fieldset>";
Page += "<fieldset>";
Page += "<legend>Wednesday Alarm</legend>";
Page +=   WedAlarmSetHTML;
Page += "</fieldset>";
Page += "<fieldset>";
Page += "<legend>Thursday Alarm</legend>";
Page +=   ThursdayAlarmSetHTML;
Page += "</fieldset>";
Page += "<fieldset>";
Page += "<legend>Friday Alarm</legend>";
Page +=   FridayAlarmSetHTML;
Page += "</fieldset>";
Page += "<fieldset>";
Page += "<legend>Saturday Alarm</legend>";
Page +=   SatAlarmSetHTML;
Page += "</fieldset>";
Page += "<fieldset>";
Page += "<legend>Sunday Alarm</legend>";
Page +=   SundayAlarmSetHTML;
Page += "</fieldset>";
Page += "<form>";
Page += "<fieldset>";
Page += "<legend>Actions</legend>";
Page += "<div>";
Page += "<br>";
Page += "<button id=\"set_button\" class=\"button\">Set</button>";
Page += "</div>";
Page += "</fieldset>";
Page += "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script><script>";
Page += "var MondayAlarmState; var MondayAlarmValue; var TuesdayAlarmState; var TuesdayAlarmValue; var WedAlarmState; var WedAlarmValue; var ThursAlarmState; var ThursAlarmValue; var FridayAlarmState; var FridayAlarmValue; var SatAlarmState; var SatAlarmValue; var SundayAlarmState; var SundayAlarmValue; $('#set_button').click(function(OnEvent){ OnEvent.preventDefault();";
Page += "MondayAlarmState = $('input[name=MondayAlarmState]:checked', '#Alarmform').val(); MondayAlarmValue = $('#MondayAlarmValue').val(); TuesdayAlarmState = $('input[name=TuesdayAlarmState]:checked', '#Alarmform').val(); TuesdayAlarmValue = $('#TuesdayAlarmValue').val(); WedAlarmState = $('input[name=WedAlarmState]:checked', '#Alarmform').val(); WedAlarmValue = $('#WedAlarmValue').val(); ThursAlarmState = $('input[name=ThursAlarmState]:checked', '#Alarmform').val();  ThursAlarmValue = $('#ThursAlarmValue').val(); FridayAlarmState = $('input[name=FridayAlarmState]:checked', '#Alarmform').val();  FridayAlarmValue = $('#FridayAlarmValue').val(); SatAlarmState = $('input[name=SatAlarmState]:checked', '#Alarmform').val(); SatAlarmValue = $('#SatAlarmValue').val(); SundayAlarmState = $('input[name=SundayAlarmState]:checked', '#Alarmform').val(); SundayAlarmValue = $('#SundayAlarmValue').val();";
Page += "$.get('/set?MondayAlarmState=' + MondayAlarmState + '&MondayAlarmValue=' + MondayAlarmValue + '&TuesdayAlarmState=' + TuesdayAlarmState + '&TuesdayAlarmValue=' + TuesdayAlarmValue + '&WedAlarmState=' + WedAlarmState + '&WedAlarmValue=' + WedAlarmValue + '&ThursAlarmState=' + ThursAlarmState + '&ThursAlarmValue=' + ThursAlarmValue + '&FridayAlarmState=' + FridayAlarmState + '&FridayAlarmValue=' + FridayAlarmValue + '&SatAlarmState=' + SatAlarmState + '&SatAlarmValue=' + SatAlarmValue + '&SundayAlarmState=' + SundayAlarmState + '&SundayAlarmValue=' + SundayAlarmValue, function(AlarmState){ console.log(AlarmState); }); });";
Page += "</script>";
Page += "</body>";
Page += "</html>";

   server.send ( 200, "text/html", Page);  
}




void handleSet() {

  struct AlarmDataStruct WebPortalAlarmSet;
  String tempTime;
  String tempHourString;
  String tempMinuteString;
  
  if (!server.authenticate(www_username, www_password)) {
    return server.requestAuthentication();
  }

  
  if(server.arg("MondayAlarmState") == "D")
  {
    WebPortalAlarmSet.AlarmOn[1] = true;
  }
  else if(server.arg("MondayAlarmState") == "O")
  {
    WebPortalAlarmSet.AlarmOn[1] = false;
  }

  if(server.arg("TuesdayAlarmState") == "D")
  {
    WebPortalAlarmSet.AlarmOn[2] = true;
  }
  else if(server.arg("TuesdayAlarmState") == "O")
  {
    WebPortalAlarmSet.AlarmOn[2] = false;
  }

  if(server.arg("WedAlarmState") == "D")
  {
    WebPortalAlarmSet.AlarmOn[3] = true;
  }
  else if(server.arg("WedAlarmState") == "O")
  {
    WebPortalAlarmSet.AlarmOn[3] = false;
  }

  if(server.arg("ThursAlarmState") == "D")
  {
    WebPortalAlarmSet.AlarmOn[4] = true;
  }
  else if(server.arg("ThursAlarmState") == "O")
  {
    WebPortalAlarmSet.AlarmOn[4] = false;
  }

  if(server.arg("FridayAlarmState") == "D")
  {
    WebPortalAlarmSet.AlarmOn[5] = true;
  }
  else if(server.arg("FridayAlarmState") == "O")
  {
    WebPortalAlarmSet.AlarmOn[5] = false;
  }

  if(server.arg("SatAlarmState") == "D")
  {
    WebPortalAlarmSet.AlarmOn[6] = true;
  }
  else if(server.arg("SatAlarmState") == "O")
  {
    WebPortalAlarmSet.AlarmOn[6] = false;
  }

  if(server.arg("SundayAlarmState") == "D")
  {
    WebPortalAlarmSet.AlarmOn[0] = true;
  }
  else if(server.arg("SundayAlarmState") == "O")
  {
    WebPortalAlarmSet.AlarmOn[0] = false;
  }

  if(server.arg("MondayAlarmValue").toInt() > 0) { 
    tempTime = server.arg("MondayAlarmValue"); 
    Serial.print("Monday Alarm Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in hour and minute form
    WebPortalAlarmSet.Hour[1] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalAlarmSet.Minute[1] = tempMinuteString.toInt();
    }

  if(server.arg("TuesdayAlarmValue").toInt() > 0) { 
    tempTime = server.arg("TuesdayAlarmValue"); 
    Serial.print("Tuesday Alarm Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in hour and minute form
    WebPortalAlarmSet.Hour[2] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalAlarmSet.Minute[2] = tempMinuteString.toInt();
    }

  if(server.arg("WedAlarmValue").toInt() > 0) { 
    tempTime = server.arg("WedAlarmValue"); 
    Serial.print("Wednesday Alarm Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in hour and minute form
    WebPortalAlarmSet.Hour[3] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalAlarmSet.Minute[3] = tempMinuteString.toInt();
    }

  if(server.arg("ThursAlarmValue").toInt() > 0) { 
    tempTime = server.arg("ThursAlarmValue"); 
    Serial.print("Thursday Alarm Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in hour and minute form
    WebPortalAlarmSet.Hour[4] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalAlarmSet.Minute[4] = tempMinuteString.toInt();
    } 

    if(server.arg("FridayAlarmValue").toInt() > 0) { 
    tempTime = server.arg("FridayAlarmValue"); 
    Serial.print("Friday Alarm Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in hour and minute form
    WebPortalAlarmSet.Hour[5] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalAlarmSet.Minute[5] = tempMinuteString.toInt();
    } 

    if(server.arg("SatAlarmValue").toInt() > 0) { 
    tempTime = server.arg("SatAlarmValue"); 
    Serial.print("Saturday Alarm Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in hour and minute form
    WebPortalAlarmSet.Hour[6] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalAlarmSet.Minute[6] = tempMinuteString.toInt();
    } 

    if(server.arg("SundayAlarmValue").toInt() > 0) { 
    tempTime = server.arg("SundayAlarmValue"); 
    Serial.print("Sunday Alarm Set for ");
    Serial.println(tempTime);
    tempHourString = tempTime.substring(0, 2); //substring is used to split the data in hour and minute form
    WebPortalAlarmSet.Hour[0] = tempHourString.toInt();
    tempMinuteString = tempTime.substring(3, 5);
    WebPortalAlarmSet.Minute[0] = tempMinuteString.toInt();
    } 

  
   EEPROM_writeAnything(100, WebPortalAlarmSet);
   ESP.restart(); 
}
   
