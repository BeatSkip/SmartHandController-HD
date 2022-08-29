// -----------------------------------------------------------------------------------
// UserInterface, handle display and keypad

#include "UserInterface.h"
#include "../../Config.h"
#include "../catalogs/Catalog.h"
#include <WaynePlexing.h>
#include <OnTask.h>

void updateWrapper() { userInterface.Run(); }
void keyPadWrapper() { keyPad.Run(); }



void UI::Init(const char version[], const int SerialBaud) {
  serialBaud = SerialBaud;
  // get guide commands ready, use single byte for SerialST4 or normal LX200 otherwise
  // SerialST4 always returns 0 "may block", Teensy and ESP32 always return > 0
  
  VF("MSG: UserInterface, start KeyPad monitor task (rate 10ms priority 1)... ");
  if (tasks.add(10, 0, true, 1, keyPadWrapper, "Keypad")) { VLF("success"); } else { VLF("FAILED!"); }
  
  strcpy(ccMe, ":Me#");
  strcpy(ccMw, ":Mw#");
  strcpy(ccMn, ":Mn#");
  strcpy(ccMs, ":Ms#");
  strcpy(ccQe, ":Qe#");
  strcpy(ccQw, ":Qw#");
  strcpy(ccQn, ":Qn#");
  strcpy(ccQs, ":Qs#");
    
  
  //Initialize LCD
  gfx->begin();
  gfx->fillScreen(BLACK);
  
  lv_init();
  
  #if USE_LV_LOG != 0
    lv_log_register_print_cb(my_print); /* register print function for debugging */
  #endif
  
  screenWidth = gfx->width(); 
  screenHeight = gfx->height();
  
  
  disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  
  if (!disp_draw_buf){
    Serial.println("LVGL disp_draw_buf allocate failed!");

  }else{
    lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 10);
  
    /* Initialize the display */
    lv_disp_drv_init(&disp_drv);
    /* Change the following line to your display resolution */
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);
  
    /* Initialize the (dummy) input device driver */
    /*Register a keypad input device*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = keyboard_read;
    indev_keypad = lv_indev_drv_register(&indev_drv);
  
    static lv_group_t * g = lv_group_create();
  
    lv_group_set_default(g);
    lv_indev_set_group(indev_keypad, g);
  
    ui_init();
  
    lv_label_set_text(ui_bootlabel, "boot done");
  }
  
  if (tasks.add(5, 0, true, 6, updateWrapper, "UIupd")) { VLF("success"); } else { VLF("FAILED!"); }

}


void UI::Run() {
    if(millis() > nexttime){
    uint32_t nextadd = lv_timer_handler();
    nexttime = millis() + nextadd;
  }
}


void UI::Connect() {
  char s[20] = "";
  int thisTry = 0;
  bool connectSuccess;

initAgain:

  lv_label_set_text(ui_bootlabel, "setting up wifi..");
  tasks.yield(2000);

  #if SERIAL_IP_MODE == STATION
    //if (firstConnect) menuWifi();
  #endif

queryAgain:
  if (thisTry % 1 == 0) lv_label_set_text(ui_bootlabel, "finding onstep.."); else lv_label_set_text(ui_bootlabel, "......");

  for (int i = 0; i < 3; i++) {
    SERIAL_ONSTEP.print(":#");
    tasks.yield(400);
    SERIAL_ONSTEP.flush();
    tasks.yield(100);
  }

  CMD_RESULT r = onStep.Get(":GVP#", s);
  if (r != CR_VALUE_GET || !strstr(s, "On-Step")) {
    if (++thisTry % 5 != 0) {
      goto queryAgain;
    } else {
      SERIAL_ONSTEP.end();
      
      tasks.yield(7000);
      thisTry = 0;
      goto initAgain;
    }
  }

  VLF("MSG: Connect, found OnStep");

again2:
  tasks.yield(1000);

  // OnStep coordinate mode for getting and setting RA/Dec
  // 0 = OBSERVED_PLACE (same as not supported)
  // 1 = TOPOCENTRIC (does refraction)
  // 2 = ASTROMETRIC_J2000 (does refraction and precession/nutation)
  thisTry = 0;
  if (onStep.Get(":GXEE#", s) == CR_VALUE_GET && s[0] >= '0' && s[0] <= '3' && s[1] == 0) {
    if (s[0] == '0') {
      telescopeCoordinates = OBSERVED_PLACE; 
      lv_label_set_text(ui_bootlabel, "Connection OK!");
      status.connected = true;
    } else 
    if (s[0] == '1') {
      telescopeCoordinates = TOPOCENTRIC; 
      lv_label_set_text(ui_bootlabel, "Connection OK!");
      status.connected = true;
    } else 
    if (s[0] == '2') {
      telescopeCoordinates = ASTROMETRIC_J2000;
      lv_label_set_text(ui_bootlabel, "Connection OK!");
      status.connected = true;
    }
  } else {
    if (++thisTry <= 3) goto again2;
    telescopeCoordinates = OBSERVED_PLACE;
    lv_label_set_text(ui_bootlabel, "Connection Error!!");
  }

  // check to see if we have auxiliary features
  hasAuxFeatures = status.featureScan();

  status.connected = true;
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
   uint32_t w = (area->x2 - area->x1 + 1);
   uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
   userInterface.gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
   userInterface.gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

   lv_disp_flush_ready(disp);
}

static void keyboard_read(lv_indev_drv_t * drv, lv_indev_data_t*data){
  static bool lastkey;

  unsigned char key = keyPad.GetLastButton();            /*Get the last pressed or released key*/
  switch (key)
  {
  case KEY_UP:
    data->key = LV_KEY_UP;
    break;
    case KEY_DOWN:
    data->key = LV_KEY_DOWN;
    break;
    case KEY_LEFT:
    data->key = LV_KEY_LEFT;
    break;
    case KEY_RIGHT:
    data->key = LV_KEY_RIGHT;
    break;
    case KEY_HOME:
    data->key = LV_KEY_ENTER;
    break;
    case KEY_F1:
    data->key = LV_KEY_NEXT;
    break;
    case KEY_F2:
    data->key = LV_KEY_PREV;
    break;
  
  default:
    break;
  }

  bool ispressed = keyPad.IsButtonPressed();

  if(ispressed) data->state = LV_INDEV_STATE_PR;
  else data->state = LV_INDEV_STATE_REL;

  #ifdef BTSK_LOG_KEYS

  if(ispressed && !lastkey){
    Serial.print("pressed ");
    switch (key)
  {
  case KEY_UP:
    data->key = LV_KEY_UP;
    Serial.println("LV_KEY_UP");
    break;
    case KEY_DOWN:
    data->key = LV_KEY_DOWN;
    Serial.println("LV_KEY_DOWN");
    break;
    case KEY_LEFT:
    data->key = LV_KEY_LEFT;
    Serial.println("LV_KEY_LEFT");
    break;
    case KEY_RIGHT:
    data->key = LV_KEY_RIGHT;
    Serial.println("LV_KEY_RIGHT");
    break;
    case KEY_HOME:
    data->key = LV_KEY_ENTER;
    Serial.println("LV_KEY_ENTER");
    break;
    case KEY_F1:
    data->key = LV_KEY_NEXT;
    Serial.println("LV_KEY_NEXT");
    break;
    case KEY_F2:
    data->key = LV_KEY_PREV;
    Serial.println("LV_KEY_PREV");
    break;
  
  default:
    break;
  }
  }
  #endif

  lastkey = ispressed;

}

UI userInterface;