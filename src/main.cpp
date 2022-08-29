#include <Arduino.h>
#include <lvgl.h>
#include "Common.h"
#include <WaynePlexing.h>
#include <OnTask.h>
#include "UserInterface/UserInterface.h"


#define Product               "HD-SHC"
#define FirmwareVersionMajor  "0"
#define FirmwareVersionMinor  "1"
#define FirmwareVersionPatch  "alpha"


const char Version[] = "Version " FirmwareVersionMajor "." FirmwareVersionMinor FirmwareVersionPatch;

void pressedCallback(unsigned char data){

}

void ReleasedCallback(unsigned char data){
  
}


void lvgl_ui_bootscreen_loaded(lv_event_t * e){
  //userInterface.Connect();
}

void setup() {
  Serial.begin(115200);
  keyPad.begin(Q1,Q2,Q3,Q4,30);
  keyPad.setPressedCallback(pressedCallback);
  keyPad.setReleasedCallback(ReleasedCallback);

  userInterface.Init(Version, 115200);
}



void loop() {
  tasks.yield();
}

