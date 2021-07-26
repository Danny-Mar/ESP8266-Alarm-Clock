#ifndef RESTORE_FACTORY_SETTINGS_H
#define RESTORE_FACTORY_SETTINGS_H

#include <EEPROM.h>
#include "EEPROMAnything.h"


void restore_factory_settings() {

for (int i = 0; i < 512; i++){
      EEPROM.write(i, NULL);
} EEPROM.commit(); //saves changes to flash

struct AlarmDataStruct AlarmSet;

for(int i=0; i<8; i++)
{
  AlarmSet.AlarmOn[i] = false;
  AlarmSet.Hour[i] = 6;
  AlarmSet.Minute[i] = 0;
}

AlarmSet.Hour[7] = '\0';
AlarmSet.Minute[7] = '\0';
AlarmSet.AlarmOn[7] = false;

EEPROM_writeAnything(100, AlarmSet);

EEPROM_writeAnything(150, "YES");

for (int i = 0; i < 512; i++){
 char temp = EEPROM.read(i);
 Serial.print(temp);
}

Serial.println("");
Serial.println("Factory Settings Restored");

}

#endif /* RESTORE_FACTORY_SETTINGS_H */
