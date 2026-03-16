#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *splash;
    lv_obj_t *main;
    lv_obj_t *obj0;
    lv_obj_t *product;
    lv_obj_t *enterbutton;
    lv_obj_t *enterlabel;
    lv_obj_t *window;
    lv_obj_t *valveled1;
    lv_obj_t *valveled2;
    lv_obj_t *valveled3;
    lv_obj_t *v1;
    lv_obj_t *v2;
    lv_obj_t *v3;
    lv_obj_t *water_scale;
    lv_obj_t *valve2_state;
    lv_obj_t *valve3_state;
    lv_obj_t *valve1_state;
    lv_obj_t *water_level;
    lv_obj_t *potdata1;
    lv_obj_t *moisture1;
    lv_obj_t *temperature1;
    lv_obj_t *pot1_moisture;
    lv_obj_t *pot1_vpd;
    lv_obj_t *pot1_humidity;
    lv_obj_t *humidity1;
    lv_obj_t *pot1_temp;
    lv_obj_t *vpd1;
    lv_obj_t *potdata2;
    lv_obj_t *moisture2;
    lv_obj_t *temperature2;
    lv_obj_t *pot2_moisture;
    lv_obj_t *pot2_vpd;
    lv_obj_t *pot2_humidity;
    lv_obj_t *humidity2;
    lv_obj_t *pot2_temp;
    lv_obj_t *vpd2;
    lv_obj_t *potdata3;
    lv_obj_t *moisture3;
    lv_obj_t *temperature3;
    lv_obj_t *pot3_moisture;
    lv_obj_t *pot3_vpd;
    lv_obj_t *pot3_humidity;
    lv_obj_t *humidity3;
    lv_obj_t *pot3_temp;
    lv_obj_t *vpd3;
    lv_obj_t *allpotset;
    lv_obj_t *allupdate;
    lv_obj_t *alltextupdate;
    lv_obj_t *sethumidity;
    lv_obj_t *settemp;
    lv_obj_t *humidity_spinbox;
    lv_obj_t *temp_spinbox;
    lv_obj_t *plushumidity;
    lv_obj_t *plushumiditytext;
    lv_obj_t *plustemp;
    lv_obj_t *plustemptext;
    lv_obj_t *minustemp;
    lv_obj_t *minustemptext;
    lv_obj_t *minushumidity;
    lv_obj_t *minushumiditytext;
    lv_obj_t *homebutton;
    lv_obj_t *hometext;
    lv_obj_t *pot1;
    lv_obj_t *tolerance_pot1;
    lv_obj_t *tolerancebox1;
    lv_obj_t *spinbox1;
    lv_obj_t *plusmoisturepot1;
    lv_obj_t *plustextpot1;
    lv_obj_t *update1;
    lv_obj_t *updatetext1;
    lv_obj_t *minusmoisturepot1;
    lv_obj_t *minustextpot1;
    lv_obj_t *moisture_pot1;
    lv_obj_t *pot2;
    lv_obj_t *tolerancebox2;
    lv_obj_t *minusmoisturepot2;
    lv_obj_t *minustextpot2;
    lv_obj_t *plusmoisturepot2;
    lv_obj_t *plustextpot2;
    lv_obj_t *moisture_pot2;
    lv_obj_t *tolerance_pot2;
    lv_obj_t *update2;
    lv_obj_t *updatetext2;
    lv_obj_t *spinbox2;
    lv_obj_t *pot3;
    lv_obj_t *tolerance_pot3;
    lv_obj_t *tolerancebox3;
    lv_obj_t *spinbox3;
    lv_obj_t *plusmoisturepot3;
    lv_obj_t *plustextpot3;
    lv_obj_t *update3;
    lv_obj_t *updatetext3;
    lv_obj_t *minusmoisturepot3;
    lv_obj_t *minustextpot3;
    lv_obj_t *moisture_pot3;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_SPLASH = 1,
    SCREEN_ID_MAIN = 2,
};

void create_screen_splash();
void tick_screen_splash();

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/