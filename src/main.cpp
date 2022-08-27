#include <Arduino.h>
#include <lvgl.h>
#include "Constants.h"
#include <WaynePlexing.h>
#include <Arduino_GFX_Library.h>
#include "ui/ui.h"
#define USE_LV_LOG 1

Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, GFX_NOT_DEFINED /* MISO */, TFT_SPI /* spi_num */);
Arduino_GFX *gfx = new Arduino_GC9A01(bus, TFT_RST, 0 /* rotation */, true /* IPS */);

WaynePlexer keyPad;
lv_indev_t * indev_keypad;
void KeyPressedToSerial(const unsigned char state);
void KeyReleasedToSerial(const unsigned char state);

/* Change to your screen resolution */
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;
long nexttime;


#if USE_LV_LOG != 0
/* Serial debugging */
void my_print(const char * file)
{

    Serial.printf("%s\r\n", file);
    Serial.flush();
}
#endif



/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
   uint32_t w = (area->x2 - area->x1 + 1);
   uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
   gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
   gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
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

  lastkey = ispressed;

}


void KeyPressedToSerial(const unsigned char state) {
  Serial.print("Key ");
  Serial.print(state,DEC);
  Serial.print(" Pressed!");
}

void KeyReleasedToSerial(const unsigned char state) {
  Serial.print(".......");
  Serial.print(state,DEC);
  Serial.println(" Released!");
}

void setup() {
  Serial.begin(115200);
  keyPad.begin(Q1,Q2,Q3,Q4,30);
  keyPad.setPressedCallback(KeyPressedToSerial);
  keyPad.setReleasedCallback(KeyReleasedToSerial);

  gfx->begin();
  gfx->fillScreen(BLACK);

  lv_init();

  #if USE_LV_LOG != 0
    lv_log_register_print_cb(my_print); /* register print function for debugging */
  #endif
   screenWidth = gfx->width();
   screenHeight = gfx->height();


   disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

   if (!disp_draw_buf)
   {
      Serial.println("LVGL disp_draw_buf allocate failed!");
   }
   else
   {
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

      Serial.println("Setup done");
   }
}

void loop() {

  if(millis() > nexttime){
    uint32_t nextadd = lv_timer_handler();
    nexttime = millis() + nextadd;
  }

  keyPad.Run();
}

