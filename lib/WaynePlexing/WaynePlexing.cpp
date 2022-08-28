#include "WaynePlexing.h"

//WaynePlexer *waynePointer; // declare a pointer to testLib class
WaynePlexer keyPad;

WaynePlexer::WaynePlexer()
{
   
}
void WaynePlexer::begin(byte pina, byte pinb, byte pinc, byte pind, int interval){
  this->pinQ1 = pina;
  this->pinQ2 = pinb;
  this->pinQ3 = pinc;
  this->pinQ4 = pind;
  this->interval = interval * 1000;
  pinMode(this->pinQ4, INPUT);
  pinMode(this->pinQ1, INPUT_PULLUP);
  pinMode(this->pinQ2, INPUT_PULLUP);
  pinMode(this->pinQ3, INPUT_PULLUP); 
  this->states[0] = 0;
  this->states[1] = 0;
  this->states[2] = 0;
  this->keyDown = false;
}


void WaynePlexer::ReleasedHandler(unsigned char state) {
  PointerToReleasedCallback(state);
}

void WaynePlexer::PressedHandler(unsigned char state) {
  PointerToPressedCallback(state);
}



void WaynePlexer::Run(void){
  unsigned long currentMillis = micros();

  if(currentMillis - previousMillis > this->interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
    RunInternal(); 
  }
}

void WaynePlexer::RunInternal(void){
  this->states[0] = this->states[1];
  this->states[1] = this->states[2];
  this->states[2] = getState();

  if(keyDown && states[1] == 0 && states[2] == 0){
    //todo: Released
    ReleasedHandler(pressed);
    keyDown = false;
    return;
  }

  if(this->states[1] == this->states[2] && this->states[0] != this->states[1] && this->states[2] != 0){
    pressed = states[2];
    keyDown = true;

    //todo: Handle key press
    PressedHandler(pressed);
  }
}


unsigned char WaynePlexer::getWayneState() {
  pinMode(this->pinQ1, INPUT_PULLUP);
  pinMode(this->pinQ2, INPUT_PULLUP);
  pinMode(this->pinQ3, INPUT_PULLUP);
  
  
  if (digitalRead(pinQ1) == LOW) {
    return 3;
  } else if (digitalRead(pinQ2) == LOW) {
    return 2;
  } else if (digitalRead(pinQ3) == LOW) {
    return 1;
  }
  pinMode(pinQ2, OUTPUT);
  digitalWrite(pinQ2, LOW);
  boolean s1 = digitalRead(pinQ1);
  boolean s3 = digitalRead(pinQ3);
  pinMode(pinQ2, INPUT_PULLUP);
  if (s1 == LOW) {
    return 5;
  } else if (s3 == LOW) {
    return 4;
  }

  pinMode(pinQ1, OUTPUT);
  digitalWrite(pinQ1, LOW);
  s3 = digitalRead(pinQ3);
  pinMode(pinQ1, INPUT_PULLUP);
  if (s3 == LOW) {
    return 6;
  }
  return 0;
}

unsigned char WaynePlexer::getState() {
  shift = (digitalRead(pinQ4) == LOW);

  unsigned char state = getWayneState();

  if(shift){
      return 7 + state;

  }else{
    return state;
  }
}

unsigned char WaynePlexer::GetPressedButton(){
  if(keyDown){
    return pressed;
  }
  return 0;
}

unsigned char WaynePlexer::GetLastButton(){
    return pressed;
}

bool WaynePlexer::IsButtonPressed(){
  return keyDown;
}