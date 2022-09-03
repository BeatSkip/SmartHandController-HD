#include <Arduino.h>
#include <lvgl.h>
#include "lv_conf.h"
#include "Common.h"
#include <WaynePlexing.h>
#include <OnTask.h>
#include <esp32-hal-psram.h>
#include "UserInterface/UserInterface.h"
#include "sd/sd_card.h"
#include "FS.h"
#include "SD_MMC.h"

#define Product               "HD-SHC"
#define FirmwareVersionMajor  "0"
#define FirmwareVersionMinor  "1"
#define FirmwareVersionPatch  "alpha"
#define LV_CONF_INCLUDE_SIMPLE

SdCard tf;

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

  psramInit();
  Serial.begin(115200);
    if(!tf.init()){
    Serial.println("Error initializing SD!");
  }

  keyPad.begin(Q1,Q2,Q3,Q4,20);
  keyPad.setPressedCallback(pressedCallback);
  keyPad.setReleasedCallback(ReleasedCallback);
  userInterface.Init(Version, 115200);

  

  
}



void loop() {
  tasks.yield();
}

