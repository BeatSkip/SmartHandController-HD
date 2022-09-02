// -----------------------------------------------------------------------------------
// UserInterface, handle display and keypad
#pragma once

#include "../Common.h"
#include <Arduino_GFX_Library.h>
#include <WaynePlexing.h>
#include <lvgl.h>
#include "ui/ui.h"

#include "../Constants.h"
#include "../status/Status.h"
#include "../onstep/OnStepCmd.h"



// coordinate mode for getting and setting RA/Dec
#define OBSERVED_PLACE 1
#define TOPOCENTRIC 2
#define ASTROMETRIC_J2000 3

#define MY_BORDER_SIZE 1
#define icon_width 16
#define icon_height 16

#define onstep_logo_width 128
#define onstep_logo_height 68


enum MENU_RESULT { MR_OK, MR_CANCEL, MR_QUIT };
enum FocusState {FS_STOPPED, FS_IN_FAST, FS_IN_SLOW, FS_OUT_SLOW, FS_OUT_FAST};
enum RotState {RS_STOPPED, RS_CW_FAST, RS_CW_SLOW, RS_CCW_SLOW, RS_CCW_FAST};

#define DisplaySettingsSize 24
typedef struct DisplaySettings {
  int32_t maxContrastSelection;
  int32_t dimTimeoutSelection;
  int32_t blankTimeoutSelection;
  uint8_t maxContrast;
  long blankTimeout;
  long dimTimeout;
} DisplaySettings;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
static void keyboard_read(lv_indev_drv_t * drv, lv_indev_data_t*data);

class UI {
public:
  void Init(const char version[], const int SerialBaud);

  void Connect();

  void DrawIntro();

  void Run();

  int telescopeCoordinates=1;

  #if DISPLAY_24HR_TIME == ON
    boolean hrs24 = true;
  #else
    boolean hrs24 = false;
  #endif

  //Keypad, LCD and GFX
  
  Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, GFX_NOT_DEFINED /* MISO */, TFT_SPI /* spi_num */);
  Arduino_GFX *gfx = new Arduino_GC9A01(bus, TFT_RST, 0 /* rotation */, true /* IPS */);
  
  lv_indev_t *indev_keypad;

  uint32_t screenWidth;
  uint32_t screenHeight;
  lv_disp_draw_buf_t draw_buf;
  lv_color_t *disp_draw_buf;
  lv_disp_drv_t disp_drv;

private:

  void menuMain();
  void menuFeatureKey();
  
  Status status;

  unsigned long maxT = 0;
  char _version[20] = "Version ?";

  DisplaySettings displaySettings = {1, 2, 3, 255, 0, 0};

  FocusState focusState = FS_STOPPED;
  RotState rotState = RS_STOPPED;

  bool firstConnect = true;
  bool hasAuxFeatures = false;
  bool sleepDisplay = false;
  bool lowContrast = false;
  int Contrast[4] = {1, 66, 192, 255};
  bool buttonCommand = false;
  bool moveNorth = false;
  bool moveSouth = false;
  bool moveEast = false;
  bool moveWest = false;

  // Guide commands
  char ccMe[5];
  char ccMw[5];
  char ccMn[5];
  char ccMs[5];
  char ccQe[5];
  char ccQw[5];
  char ccQn[5];
  char ccQs[5];

  bool GuidebuttonsEnabled = false;

  unsigned long lastpageupdate = millis();
  unsigned long time_last_action = millis();
  unsigned long time_keep_alive = millis();

  byte page = 0;
  uint8_t current_selection_L0 = 1;
  uint8_t current_selection_L1 = 1;
  uint8_t current_selection_L2 = 1;
  uint8_t current_selection_L3 = 1;
  uint8_t current_selection_L4 = 1;
  bool    current_selection_filter_above = true;
  uint8_t current_selection_filter_con = 1;
  uint8_t current_selection_filter_type = 1;
  uint8_t current_selection_filter_byMag = 1;
  uint8_t current_selection_filter_nearby = 1;
  uint8_t current_selection_filter_dblmin = 1;
  uint8_t current_selection_filter_dblmax = 1;
  uint8_t current_selection_filter_varmax = 1;
  uint8_t activeGuideRate = 5;
  uint8_t featureKeyMode = 1; // guide rate

  long angleRA = 0;
  long angleDEC = 0;

  long serialBaud = 115200;
  long nexttime;

};

extern UI userInterface;
