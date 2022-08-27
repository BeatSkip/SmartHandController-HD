#ifndef WAYNEPLEXING_H
#define WAYNEPLEXING_H

#include <Arduino.h>


class WaynePlexer {
  private:
    byte pinQ1;
    byte pinQ2;
    byte pinQ3;
    byte pinQ4;
    bool shift;
    bool keyDown;

    int interval;
    int stateindex;
    unsigned char states[3];
    unsigned char pressed;
    void (*PointerToPressedCallback)(const unsigned char);
    void (*PointerToReleasedCallback)(const unsigned char);

    unsigned long previousMillis;
    void RunInternal(void);
    unsigned char getWayneState(void);
    unsigned char getState(void);
  public:
    // Setup pin LED and call init()
    void begin(byte pina, byte pinb, byte pinc, byte pind, int interval);
    void ReleasedHandler(unsigned char state);
    void PressedHandler(unsigned char state);
    
    void setPressedCallback(void (*Callback)(const unsigned char)) {
                      PointerToPressedCallback = Callback; }

    void setReleasedCallback(void (*Callback)(const unsigned char)) {
                      PointerToReleasedCallback = Callback; }
                      
    void Run(void);
    unsigned char GetPressedButton();
    unsigned char GetLastButton();
    bool IsButtonPressed();

    // Power off the LED
    void off();
};
#endif