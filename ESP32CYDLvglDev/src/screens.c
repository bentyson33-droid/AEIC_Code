#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_splash() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.splash = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff84cc87), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // Product
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.product = obj;
            lv_obj_set_pos(obj, 60, 21);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Automatic Environment \n& Irrirgation Controller");
        }
        {
            // enterbutton
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.enterbutton = obj;
            lv_obj_set_pos(obj, 119, 181);
            lv_obj_set_size(obj, 82, 34);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // enterlabel
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.enterlabel = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Enter");
                }
            }
        }
    }
    
    tick_screen_splash();
}

void tick_screen_splash() {
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Window
            lv_obj_t *obj = lv_tabview_create(parent_obj);
            objects.window = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 320, 240);
            lv_tabview_set_tab_bar_position(obj, LV_DIR_TOP);
            lv_tabview_set_tab_bar_size(obj, 32);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW);
            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Water ");
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // valveled1
                            lv_obj_t *obj = lv_led_create(parent_obj);
                            objects.valveled1 = obj;
                            lv_obj_set_pos(obj, 227, 36);
                            lv_obj_set_size(obj, 15, 15);
                            lv_led_set_color(obj, lv_color_hex(0xff686878));
                            lv_led_set_brightness(obj, 255);
                        }
                        {
                            // valveled2
                            lv_obj_t *obj = lv_led_create(parent_obj);
                            objects.valveled2 = obj;
                            lv_obj_set_pos(obj, 227, 98);
                            lv_obj_set_size(obj, 15, 15);
                            lv_led_set_color(obj, lv_color_hex(0xff6b6b7a));
                            lv_led_set_brightness(obj, 255);
                        }
                        {
                            // valveled3
                            lv_obj_t *obj = lv_led_create(parent_obj);
                            objects.valveled3 = obj;
                            lv_obj_set_pos(obj, 227, 159);
                            lv_obj_set_size(obj, 15, 15);
                            lv_led_set_color(obj, lv_color_hex(0xff6d6d7c));
                            lv_led_set_brightness(obj, 255);
                        }
                        {
                            // V1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.v1 = obj;
                            lv_obj_set_pos(obj, 165, 4);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Valve 1");
                        }
                        {
                            // V2
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.v2 = obj;
                            lv_obj_set_pos(obj, 167, 65);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Valve 2");
                        }
                        {
                            // V3
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.v3 = obj;
                            lv_obj_set_pos(obj, 167, 130);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "Valve 3");
                        }
                        {
                            // Water Scale
                            lv_obj_t *obj = lv_scale_create(parent_obj);
                            objects.water_scale = obj;
                            lv_obj_set_pos(obj, 88, 45);
                            lv_obj_set_size(obj, 51, 136);
                            lv_scale_set_mode(obj, LV_SCALE_MODE_VERTICAL_RIGHT);
                            lv_scale_set_range(obj, 0, 100);
                            lv_scale_set_total_tick_count(obj, 10);
                            lv_scale_set_major_tick_every(obj, 10);
                            lv_scale_set_label_show(obj, true);
                            lv_obj_set_style_length(obj, 5, LV_PART_ITEMS | LV_STATE_DEFAULT);
                            lv_obj_set_style_length(obj, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 12, 7);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Water Tank \nLevel");
                        }
                        {
                            // valve2_state
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.valve2_state = obj;
                            lv_obj_set_pos(obj, 182, 98);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "--");
                        }
                        {
                            // valve3_state
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.valve3_state = obj;
                            lv_obj_set_pos(obj, 182, 158);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "--");
                        }
                        {
                            // valve1_state
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.valve1_state = obj;
                            lv_obj_set_pos(obj, 182, 35);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_label_set_text(obj, "--");
                        }
                        {
                            // Water Level
                            lv_obj_t *obj = lv_bar_create(parent_obj);
                            objects.water_level = obj;
                            lv_obj_set_pos(obj, 22, 45);
                            lv_obj_set_size(obj, 66, 136);
                            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Data");
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_tabview_create(parent_obj);
                            lv_obj_set_pos(obj, -13, -12);
                            lv_obj_set_size(obj, 320, 208);
                            lv_tabview_set_tab_bar_position(obj, LV_DIR_TOP);
                            lv_tabview_set_tab_bar_size(obj, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // potdata1
                                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Pot 1");
                                    objects.potdata1 = obj;
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // Moisture1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.moisture1 = obj;
                                            lv_obj_set_pos(obj, 82, 19);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Moisture:");
                                        }
                                        {
                                            // Temperature1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.temperature1 = obj;
                                            lv_obj_set_pos(obj, 51, 49);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Temperature:");
                                        }
                                        {
                                            // pot1_moisture
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.pot1_moisture = obj;
                                            lv_obj_set_pos(obj, 186, 19);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "--");
                                        }
                                        {
                                            // pot1_vpd
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.pot1_vpd = obj;
                                            lv_obj_set_pos(obj, 186, 114);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "--");
                                        }
                                        {
                                            // pot1_humidity
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.pot1_humidity = obj;
                                            lv_obj_set_pos(obj, 186, 82);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "--");
                                        }
                                        {
                                            // Humidity1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.humidity1 = obj;
                                            lv_obj_set_pos(obj, 78, 82);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Humidity:");
                                        }
                                        {
                                            // pot1_temp
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.pot1_temp = obj;
                                            lv_obj_set_pos(obj, 186, 49);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "--");
                                        }
                                        {
                                            // VPD1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.vpd1 = obj;
                                            lv_obj_set_pos(obj, 114, 114);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "VPD:");
                                        }
                                    }
                                }
                                {
                                    // potdata2
                                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Pot 2");
                                    objects.potdata2 = obj;
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // Moisture2
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.moisture2 = obj;
                                            lv_obj_set_pos(obj, 82, 19);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Moisture:");
                                        }
                                        {
                                            // Temperature2
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.temperature2 = obj;
                                            lv_obj_set_pos(obj, 51, 49);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Temperature:");
                                        }
                                        {
                                            // pot2_moisture
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.pot2_moisture = obj;
                                            lv_obj_set_pos(obj, 186, 19);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "--");
                                        }
                                        {
                                            // pot2_vpd
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.pot2_vpd = obj;
                                            lv_obj_set_pos(obj, 186, 114);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "--");
                                        }
                                        {
                                            // pot2_humidity
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.pot2_humidity = obj;
                                            lv_obj_set_pos(obj, 186, 82);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "--");
                                        }
                                        {
                                            // Humidity2
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.humidity2 = obj;
                                            lv_obj_set_pos(obj, 78, 82);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Humidity:");
                                        }
                                        {
                                            // pot2_temp
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.pot2_temp = obj;
                                            lv_obj_set_pos(obj, 186, 49);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "--");
                                        }
                                        {
                                            // VPD2
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.vpd2 = obj;
                                            lv_obj_set_pos(obj, 114, 114);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "VPD:");
                                        }
                                    }
                                }
                                {
                                    // potdata3
                                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Pot 3");
                                    objects.potdata3 = obj;
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // Moisture3
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.moisture3 = obj;
                                            lv_obj_set_pos(obj, 82, 19);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Moisture:");
                                        }
                                        {
                                            // Temperature3
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.temperature3 = obj;
                                            lv_obj_set_pos(obj, 51, 49);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Temperature:");
                                        }
                                        {
                                            // pot3_moisture
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.pot3_moisture = obj;
                                            lv_obj_set_pos(obj, 186, 19);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "--");
                                        }
                                        {
                                            // pot3_vpd
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.pot3_vpd = obj;
                                            lv_obj_set_pos(obj, 186, 114);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "--");
                                        }
                                        {
                                            // pot3_humidity
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.pot3_humidity = obj;
                                            lv_obj_set_pos(obj, 186, 82);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "--");
                                        }
                                        {
                                            // Humidity3
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.humidity3 = obj;
                                            lv_obj_set_pos(obj, 78, 82);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Humidity:");
                                        }
                                        {
                                            // pot3_temp
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.pot3_temp = obj;
                                            lv_obj_set_pos(obj, 186, 49);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "--");
                                        }
                                        {
                                            // VPD3
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.vpd3 = obj;
                                            lv_obj_set_pos(obj, 114, 114);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "VPD:");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                {
                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Settings");
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_tabview_create(parent_obj);
                            lv_obj_set_pos(obj, -13, -12);
                            lv_obj_set_size(obj, 320, 207);
                            lv_tabview_set_tab_bar_position(obj, LV_DIR_TOP);
                            lv_tabview_set_tab_bar_size(obj, 32);
                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                            lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                            lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
                            lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
                            lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
                            {
                                lv_obj_t *parent_obj = obj;
                                {
                                    // allpotset
                                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "All");
                                    objects.allpotset = obj;
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
                                    lv_obj_set_scroll_dir(obj, LV_DIR_NONE);
                                    lv_obj_set_scroll_snap_x(obj, LV_SCROLL_SNAP_NONE);
                                    lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // allupdate
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.allupdate = obj;
                                            lv_obj_set_pos(obj, 224, 24);
                                            lv_obj_set_size(obj, 66, 35);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // alltextupdate
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.alltextupdate = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "Update");
                                                }
                                            }
                                        }
                                        {
                                            // tolerancehumidity
                                            lv_obj_t *obj = lv_dropdown_create(parent_obj);
                                            objects.tolerancehumidity = obj;
                                            lv_obj_set_pos(obj, 62, 96);
                                            lv_obj_set_size(obj, 79, LV_SIZE_CONTENT);
                                            lv_dropdown_set_options(obj, "+/- 1%\n+/- 3%\n+/- 5%");
                                            lv_dropdown_set_selected(obj, 0);
                                        }
                                        {
                                            // tolerancetemp
                                            lv_obj_t *obj = lv_dropdown_create(parent_obj);
                                            objects.tolerancetemp = obj;
                                            lv_obj_set_pos(obj, 62, 29);
                                            lv_obj_set_size(obj, 79, LV_SIZE_CONTENT);
                                            lv_dropdown_set_options(obj, "+/- 1%\n+/- 3%\n+/- 5%");
                                            lv_dropdown_set_selected(obj, 0);
                                        }
                                        {
                                            // sethumidity
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.sethumidity = obj;
                                            lv_obj_set_pos(obj, 20, 73);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Humidity (%):");
                                        }
                                        {
                                            // settemp
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.settemp = obj;
                                            lv_obj_set_pos(obj, 5, 3);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Temperature (°F):");
                                        }
                                        {
                                            // HumiditySpinbox
                                            lv_obj_t *obj = lv_spinbox_create(parent_obj);
                                            objects.humidity_spinbox = obj;
                                            lv_obj_set_pos(obj, 5, 98);
                                            lv_obj_set_size(obj, 50, 36);
                                            lv_spinbox_set_digit_format(obj, 3, 0);
                                            lv_spinbox_set_range(obj, 0, 100);
                                            lv_spinbox_set_rollover(obj, false);
                                            lv_spinbox_set_step(obj, 1);
                                            lv_spinbox_set_value(obj, 50);
                                        }
                                        {
                                            // TempSpinbox
                                            lv_obj_t *obj = lv_spinbox_create(parent_obj);
                                            objects.temp_spinbox = obj;
                                            lv_obj_set_pos(obj, 5, 29);
                                            lv_obj_set_size(obj, 50, 36);
                                            lv_spinbox_set_digit_format(obj, 3, 0);
                                            lv_spinbox_set_range(obj, 0, 100);
                                            lv_spinbox_set_rollover(obj, false);
                                            lv_spinbox_set_step(obj, 1);
                                            lv_spinbox_set_value(obj, 75);
                                        }
                                        {
                                            // plushumidity
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.plushumidity = obj;
                                            lv_obj_set_pos(obj, 156, 78);
                                            lv_obj_set_size(obj, 50, 35);
                                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff50cd23), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // plushumiditytext
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.plushumiditytext = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "+");
                                                }
                                            }
                                        }
                                        {
                                            // plustemp
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.plustemp = obj;
                                            lv_obj_set_pos(obj, 156, -5);
                                            lv_obj_set_size(obj, 50, 35);
                                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff50cd23), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // plustemptext
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.plustemptext = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "+");
                                                }
                                            }
                                        }
                                        {
                                            // minustemp
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.minustemp = obj;
                                            lv_obj_set_pos(obj, 156, 36);
                                            lv_obj_set_size(obj, 50, 35);
                                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff25d3e), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // minustemptext
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.minustemptext = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "-");
                                                }
                                            }
                                        }
                                        {
                                            // minushumidity
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.minushumidity = obj;
                                            lv_obj_set_pos(obj, 156, 120);
                                            lv_obj_set_size(obj, 50, 35);
                                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff25d3e), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // minushumiditytext
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.minushumiditytext = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "-");
                                                }
                                            }
                                        }
                                        {
                                            // homebutton
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.homebutton = obj;
                                            lv_obj_set_pos(obj, 224, 83);
                                            lv_obj_set_size(obj, 66, 35);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // hometext
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.hometext = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "Home");
                                                }
                                            }
                                        }
                                    }
                                }
                                {
                                    // pot1
                                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Pot 1");
                                    objects.pot1 = obj;
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // TolerancePot1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.tolerance_pot1 = obj;
                                            lv_obj_set_pos(obj, 193, 15);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Tolerance (%)");
                                        }
                                        {
                                            // tolerancebox1
                                            lv_obj_t *obj = lv_dropdown_create(parent_obj);
                                            objects.tolerancebox1 = obj;
                                            lv_obj_set_pos(obj, 201, 43);
                                            lv_obj_set_size(obj, 79, LV_SIZE_CONTENT);
                                            lv_dropdown_set_options(obj, "+/- 1%\n+/- 3%\n+/- 5%");
                                            lv_dropdown_set_selected(obj, 0);
                                        }
                                        {
                                            // spinbox1
                                            lv_obj_t *obj = lv_spinbox_create(parent_obj);
                                            objects.spinbox1 = obj;
                                            lv_obj_set_pos(obj, 33, 43);
                                            lv_obj_set_size(obj, 53, 36);
                                            lv_spinbox_set_digit_format(obj, 3, 0);
                                            lv_spinbox_set_range(obj, 0, 100);
                                            lv_spinbox_set_rollover(obj, false);
                                            lv_spinbox_set_step(obj, 1);
                                            lv_spinbox_set_value(obj, 80);
                                            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SNAPPABLE);
                                        }
                                        {
                                            // plusmoisturepot1
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.plusmoisturepot1 = obj;
                                            lv_obj_set_pos(obj, 128, 3);
                                            lv_obj_set_size(obj, 40, 40);
                                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff50cd23), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // plustextpot1
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.plustextpot1 = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "+");
                                                }
                                            }
                                        }
                                        {
                                            // update1
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.update1 = obj;
                                            lv_obj_set_pos(obj, 104, 112);
                                            lv_obj_set_size(obj, 87, 37);
                                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff389ae9), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // updatetext1
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.updatetext1 = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "Update");
                                                }
                                            }
                                        }
                                        {
                                            // minusmoisturepot1
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.minusmoisturepot1 = obj;
                                            lv_obj_set_pos(obj, 128, 55);
                                            lv_obj_set_size(obj, 40, 40);
                                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff25d3e), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // minustextpot1
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.minustextpot1 = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "-");
                                                }
                                            }
                                        }
                                        {
                                            // MoisturePot1
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.moisture_pot1 = obj;
                                            lv_obj_set_pos(obj, 14, 15);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Moisture (%)");
                                        }
                                    }
                                }
                                {
                                    // pot2
                                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Pot 2");
                                    objects.pot2 = obj;
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // tolerancebox2
                                            lv_obj_t *obj = lv_dropdown_create(parent_obj);
                                            objects.tolerancebox2 = obj;
                                            lv_obj_set_pos(obj, 201, 43);
                                            lv_obj_set_size(obj, 79, LV_SIZE_CONTENT);
                                            lv_dropdown_set_options(obj, "+/- 1%\n+/- 3%\n+/- 5%");
                                            lv_dropdown_set_selected(obj, 0);
                                        }
                                        {
                                            // minusmoisturepot2
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.minusmoisturepot2 = obj;
                                            lv_obj_set_pos(obj, 128, 55);
                                            lv_obj_set_size(obj, 40, 40);
                                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff25d3e), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // minustextpot2
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.minustextpot2 = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "-");
                                                }
                                            }
                                        }
                                        {
                                            // plusmoisturepot2
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.plusmoisturepot2 = obj;
                                            lv_obj_set_pos(obj, 128, 3);
                                            lv_obj_set_size(obj, 40, 40);
                                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff50cd23), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // plustextpot2
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.plustextpot2 = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "+");
                                                }
                                            }
                                        }
                                        {
                                            // MoisturePot2
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.moisture_pot2 = obj;
                                            lv_obj_set_pos(obj, 14, 15);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Moisture (%)");
                                        }
                                        {
                                            // TolerancePot2
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.tolerance_pot2 = obj;
                                            lv_obj_set_pos(obj, 193, 15);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Tolerance (%)");
                                        }
                                        {
                                            // update2
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.update2 = obj;
                                            lv_obj_set_pos(obj, 104, 112);
                                            lv_obj_set_size(obj, 87, 37);
                                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff389ae9), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // updatetext2
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.updatetext2 = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "Update");
                                                }
                                            }
                                        }
                                        {
                                            // spinbox2
                                            lv_obj_t *obj = lv_spinbox_create(parent_obj);
                                            objects.spinbox2 = obj;
                                            lv_obj_set_pos(obj, 33, 43);
                                            lv_obj_set_size(obj, 53, 36);
                                            lv_spinbox_set_digit_format(obj, 3, 0);
                                            lv_spinbox_set_range(obj, 0, 100);
                                            lv_spinbox_set_rollover(obj, false);
                                            lv_spinbox_set_step(obj, 1);
                                            lv_spinbox_set_value(obj, 80);
                                        }
                                    }
                                }
                                {
                                    // pot3
                                    lv_obj_t *obj = lv_tabview_add_tab(parent_obj, "Pot 3");
                                    objects.pot3 = obj;
                                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
                                    {
                                        lv_obj_t *parent_obj = obj;
                                        {
                                            // TolerancePot3
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.tolerance_pot3 = obj;
                                            lv_obj_set_pos(obj, 193, 15);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Tolerance (%)");
                                        }
                                        {
                                            // tolerancebox3
                                            lv_obj_t *obj = lv_dropdown_create(parent_obj);
                                            objects.tolerancebox3 = obj;
                                            lv_obj_set_pos(obj, 201, 43);
                                            lv_obj_set_size(obj, 79, LV_SIZE_CONTENT);
                                            lv_dropdown_set_options(obj, "+/- 1%\n+/- 3%\n+/- 5%");
                                            lv_dropdown_set_selected(obj, 0);
                                        }
                                        {
                                            // spinbox3
                                            lv_obj_t *obj = lv_spinbox_create(parent_obj);
                                            objects.spinbox3 = obj;
                                            lv_obj_set_pos(obj, 33, 43);
                                            lv_obj_set_size(obj, 53, 36);
                                            lv_spinbox_set_digit_format(obj, 3, 0);
                                            lv_spinbox_set_range(obj, 0, 100);
                                            lv_spinbox_set_rollover(obj, false);
                                            lv_spinbox_set_step(obj, 1);
                                            lv_spinbox_set_value(obj, 80);
                                        }
                                        {
                                            // plusmoisturepot3
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.plusmoisturepot3 = obj;
                                            lv_obj_set_pos(obj, 128, 3);
                                            lv_obj_set_size(obj, 40, 40);
                                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff50cd23), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // plustextpot3
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.plustextpot3 = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "+");
                                                }
                                            }
                                        }
                                        {
                                            // update3
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.update3 = obj;
                                            lv_obj_set_pos(obj, 104, 112);
                                            lv_obj_set_size(obj, 87, 37);
                                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff389ae9), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // updatetext3
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.updatetext3 = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "Update");
                                                }
                                            }
                                        }
                                        {
                                            // minusmoisturepot3
                                            lv_obj_t *obj = lv_button_create(parent_obj);
                                            objects.minusmoisturepot3 = obj;
                                            lv_obj_set_pos(obj, 128, 55);
                                            lv_obj_set_size(obj, 40, 40);
                                            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff25d3e), LV_PART_MAIN | LV_STATE_DEFAULT);
                                            {
                                                lv_obj_t *parent_obj = obj;
                                                {
                                                    // minustextpot3
                                                    lv_obj_t *obj = lv_label_create(parent_obj);
                                                    objects.minustextpot3 = obj;
                                                    lv_obj_set_pos(obj, 0, 0);
                                                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                                                    lv_label_set_text(obj, "-");
                                                }
                                            }
                                        }
                                        {
                                            // MoisturePot3
                                            lv_obj_t *obj = lv_label_create(parent_obj);
                                            objects.moisture_pot3 = obj;
                                            lv_obj_set_pos(obj, 14, 15);
                                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                                            lv_label_set_text(obj, "Moisture (%)");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_splash,
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_splash();
    create_screen_main();
}
