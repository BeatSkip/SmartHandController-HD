#include <Arduino.h>
#include <lvgl.h>
#include "lv_conf.h"
#include "Common.h"
#include <WaynePlexing.h>
#include <OnTask.h>
#include "UserInterface/UserInterface.h"
 
#define Product               "HD-SHC"
#define FirmwareVersionMajor  "0"
#define FirmwareVersionMinor  "1"
#define FirmwareVersionPatch  "alpha"
#define LV_CONF_INCLUDE_SIMPLE


const char Version[] = "Version " FirmwareVersionMajor "." FirmwareVersionMinor FirmwareVersionPatch;

void pressedCallback(unsigned char data){
 Serial.print("Pressed key ");
 Serial.println(data,DEC);

}

void pressedCallbackA(unsigned char data){
 Serial.print("A - Pressed key ");
 Serial.println(data,DEC);

}

void pressedCallbackB(unsigned char data){
 Serial.print("B - Pressed key ");
 Serial.println(data,DEC);

}

void pressedCallbackC(unsigned char data){
 Serial.print("C - Pressed key ");
 Serial.println(data,DEC);

}

void ReleasedCallback(unsigned char data){
  
}


void lvgl_ui_bootscreen_loaded(lv_event_t * e){
  //userInterface.Connect();
}

void setup() {
  Serial.begin(115200);

  keyPad.begin(Q2,Q1,Q3,Q4,20);
  keyPad.setPressedCallback(pressedCallback);
  keyPad.setReleasedCallback(ReleasedCallback);
  userInterface.Init(Version, 115200);
}



void loop() {
  tasks.yield();
}

