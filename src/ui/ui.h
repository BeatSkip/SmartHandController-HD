// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: SHC

#ifndef _SHC_UI_H
#define _SHC_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

extern lv_obj_t * ui_Boot;
extern lv_obj_t * ui_Image1;
extern lv_obj_t * ui_Image2;
extern lv_obj_t * ui_bootspinner;
extern lv_obj_t * ui_bootlabel;
extern lv_obj_t * ui_MainMenu;
extern lv_obj_t * ui_Roller1;


LV_IMG_DECLARE(ui_img_664584034);    // assets\HD-SHC-Boot.png
LV_IMG_DECLARE(ui_img_1203702338);    // assets\boot-logo.png




void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
