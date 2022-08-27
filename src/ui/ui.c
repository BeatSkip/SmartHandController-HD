// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: SHC

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Boot;
lv_obj_t * ui_Image1;
lv_obj_t * ui_Image2;
lv_obj_t * ui_bootspinner;
lv_obj_t * ui_bootlabel;
lv_obj_t * ui_MainMenu;
lv_obj_t * ui_Roller1;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "#error LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
static void ui_event_Boot(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_SCREEN_LOADED) {
        _ui_screen_change(ui_MainMenu, LV_SCR_LOAD_ANIM_FADE_ON, 500, 2500);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Boot_screen_init(void)
{

    // ui_Boot

    ui_Boot = lv_obj_create(NULL);

    lv_obj_add_state(ui_Boot, LV_STATE_FOCUSED);

    lv_obj_clear_flag(ui_Boot, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_event_cb(ui_Boot, ui_event_Boot, LV_EVENT_ALL, NULL);

    // ui_Image1

    ui_Image1 = lv_img_create(ui_Boot);
    lv_img_set_src(ui_Image1, &ui_img_664584034);

    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image1, 0);
    lv_obj_set_y(ui_Image1, 0);

    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Image2

    ui_Image2 = lv_img_create(ui_Boot);
    lv_img_set_src(ui_Image2, &ui_img_1203702338);

    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Image2, 0);
    lv_obj_set_y(ui_Image2, 0);

    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);

    // ui_bootspinner

    ui_bootspinner = lv_spinner_create(ui_Boot, 1000, 90);

    lv_obj_set_width(ui_bootspinner, 40);
    lv_obj_set_height(ui_bootspinner, 40);

    lv_obj_set_x(ui_bootspinner, 0);
    lv_obj_set_y(ui_bootspinner, 60);

    lv_obj_set_align(ui_bootspinner, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_bootspinner, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_set_style_arc_width(ui_bootspinner, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_arc_width(ui_bootspinner, 5, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // ui_bootlabel

    ui_bootlabel = lv_label_create(ui_Boot);

    lv_obj_set_width(ui_bootlabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_bootlabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_bootlabel, 0);
    lv_obj_set_y(ui_bootlabel, -60);

    lv_obj_set_align(ui_bootlabel, LV_ALIGN_CENTER);

    lv_label_set_text(ui_bootlabel, "Connecting...");

}
void ui_MainMenu_screen_init(void)
{

    // ui_MainMenu

    ui_MainMenu = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_MainMenu, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Roller1

    ui_Roller1 = lv_roller_create(ui_MainMenu);
    lv_roller_set_options(ui_Roller1, "Option 1\nOption 2\nOption 3", LV_ROLLER_MODE_NORMAL);

    lv_obj_set_width(ui_Roller1, 200);
    lv_obj_set_height(ui_Roller1, 200);

    lv_obj_set_x(ui_Roller1, 0);
    lv_obj_set_y(ui_Roller1, 0);

    lv_obj_set_align(ui_Roller1, LV_ALIGN_CENTER);

    lv_obj_set_style_radius(ui_Roller1, 100, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_Roller1, 10, LV_PART_SELECTED | LV_STATE_DEFAULT);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Boot_screen_init();
    ui_MainMenu_screen_init();
    lv_disp_load_scr(ui_Boot);
}

