
// SERIAL PORTS --------------------------------------------------------------------------------------------------------------------
#define SERIAL_ONSTEP                 Serial // .._ST4, SERIAL_ST4 for ST4 port sync comms, you can also use any other available Infreq
                                            //         serial port (if pins are unused,) Serial3 on the Teensy3.2 or SERIAL_IP
                                            //         for example.  This is the serial interface connected to OnStep.
#define SERIAL_ONSTEP_BAUD_DEFAULT   115200 //   9600, Common baud rates for these parameters are 9600,19200,57600,115200.      Infreq
                                          //         Only used for async serial communication with OnStep.

// USER FEEDBACK -------------------------------------------------------------------------------------------------------------------
#define UTILITY_LIGHT                 OFF //    OFF, n. Where n=0..255 (0..100%) activates feature sets default brightness.   Adjust

// DISPLAY -------------------------------------------------------------------------------------------------------------------------
#define DISPLAY_AMBIENT_CONDITIONS    OFF //    OFF, ON to show ambient conditions in the display rotation                    Option
#define DISPLAY_WRAP_MENUS            OFF //    OFF, ON allows menus to wrap so moving past bottom returns to top, etc.       Option
#define DISPLAY_24HR_TIME              ON //     ON, OFF to use 12 hour format for entering time.                             Option

// CATALOGS ------------------------------------------------------------------------------------------------------------------------
// Advanced users can also customize which celestial object catalogs are included or even add new catalogs using Config.catalogs.h

// THAT'S IT FOR USER CONFIGURATION!

// ---------------------------------------------------------------------------------------------------------------------------------
#include "Config.Extended.h"