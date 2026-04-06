#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include "ui.h"
#include <math.h>

// ================= DEVICE DEFINES =================
#define DEVICE_TYPE_CYD  0x02
#define TARGET_XIAO_ADDR 1

// ================= XIAO MAC =======================
uint8_t xiaoMAC[] = {0x58, 0x8C, 0x81, 0xA4, 0xCC, 0x14};

// ================= PACKETS ========================
typedef struct __attribute__((packed)) {
    uint8_t set;
    uint8_t DB;
    boolean override;
} moisture_packet_t;

typedef struct __attribute__((packed)) {
    uint8_t devAddr;
    uint8_t devType;
    uint8_t valve_state;
    float temperature;
    float humidity;
    float soil_moisture;
} status_packet_t;

typedef struct __attribute__((packed)) {
    uint8_t devAddr;
    boolean override;
    boolean valve_state;
}   manual_packet_t;

// =============== STRUCTURE ARRAY ================
status_packet_t potsStruct[3];

// ================= TOUCHSCREEN ==================
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

// ================= DISPLAY ======================
#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))

uint32_t draw_buf[DRAW_BUF_SIZE / 4];
TFT_eSPI tft = TFT_eSPI();

// ================= PROTOTYPES ===================
void touchscreen_read(lv_indev_t *, lv_indev_data_t *);
void onDataRecv(const uint8_t *, const uint8_t *, int);
void automaticbutton_cb(lv_event_t * e);
void manualbutton_cb(lv_event_t * e);
void homebutton_cb(lv_event_t * e);
void homebuttonman_cb(lv_event_t * e);
void moisture_plus_cb(lv_event_t * e);
void moisture_minus_cb(lv_event_t * e);
void update_pot_cb(lv_event_t * e);
void allupdate_cb(lv_event_t * e);
int getToleranceValue(lv_obj_t * dropdown);
float calculateTolerance(float target, float tolerancePercent);

// ================= SEND COMMAND =================
// void sendMoistureTarget() {
//     moisture_packet_t cmd;
//      cmd.set = moisturespinbox
//      cmd.DB = moistureDB
//      cmd.override = 0
//     cmd.moisture = moisture;

//     esp_now_send(xiaoMAC, (uint8_t*)&cmd, sizeof(cmd));
//     delay(2500);
// }

//void sendGreenHouseTarget() {
//     greenhouse_packet_t packet;
//     packet.type = 0;
//     packet.temp_target = lv_spinbox_get_value(objects.temp_spinbox);
//     packet.humidity_target = lv_spinbox_get_value(objects.humidity_spinbox);

//     esp_now_send(xiaoMAC, (uint8_t*)&packet, sizeof(packet));
// }

// ================= SETUP ========================
void setup() {

    Serial.begin(9600);
    WiFi.mode(WIFI_STA);

    // ----- ESP-NOW -----
    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW init failed");
        return;
    }

    esp_now_register_recv_cb(onDataRecv);

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, xiaoMAC, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    esp_now_add_peer(&peerInfo);

    for (int i = 0; i < 3; i++) {
        potsStruct[i].temperature = NAN;
        potsStruct[i].humidity = NAN;
        potsStruct[i].soil_moisture = NAN;
    }

    // ----- LVGL -----
    lv_init();

    touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchscreen.begin(touchscreenSPI);
    touchscreen.setRotation(2);

    lv_display_t *disp = lv_tft_espi_create(
    SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);

    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, touchscreen_read);

    // Initialize EEZ UI
    ui_init();

    lv_obj_add_event_cb(objects.automaticbutton, automaticbutton_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.manualbutton, manualbutton_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.homebutton, homebutton_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(objects.homebuttonman, homebuttonman_cb, LV_EVENT_CLICKED, NULL);

    // POT 1
    lv_obj_add_event_cb(objects.plusmoisturepot1, moisture_plus_cb, LV_EVENT_PRESSED, objects.spinbox1);
    lv_obj_add_event_cb(objects.plusmoisturepot1, moisture_plus_cb, LV_EVENT_LONG_PRESSED_REPEAT, objects.spinbox1);
    lv_obj_add_event_cb(objects.minusmoisturepot1, moisture_minus_cb, LV_EVENT_PRESSED, objects.spinbox1);
    lv_obj_add_event_cb(objects.minusmoisturepot1, moisture_minus_cb, LV_EVENT_LONG_PRESSED_REPEAT, objects.spinbox1);
    lv_obj_clear_flag(objects.spinbox1, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_set_style_text_align(objects.spinbox1, LV_TEXT_ALIGN_CENTER, 0);

    // POT 2
    lv_obj_add_event_cb(objects.plusmoisturepot2, moisture_plus_cb, LV_EVENT_PRESSED, objects.spinbox2);
    lv_obj_add_event_cb(objects.plusmoisturepot2, moisture_plus_cb, LV_EVENT_LONG_PRESSED_REPEAT, objects.spinbox2);
    lv_obj_add_event_cb(objects.minusmoisturepot2, moisture_minus_cb, LV_EVENT_PRESSED, objects.spinbox2);
    lv_obj_add_event_cb(objects.minusmoisturepot2, moisture_minus_cb, LV_EVENT_LONG_PRESSED_REPEAT, objects.spinbox2);
    lv_obj_clear_flag(objects.spinbox2, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_set_style_text_align(objects.spinbox2, LV_TEXT_ALIGN_CENTER, 0);

    // POT 3
    lv_obj_add_event_cb(objects.plusmoisturepot3, moisture_plus_cb, LV_EVENT_PRESSED, objects.spinbox3);
    lv_obj_add_event_cb(objects.plusmoisturepot3, moisture_plus_cb, LV_EVENT_LONG_PRESSED_REPEAT, objects.spinbox3);
    lv_obj_add_event_cb(objects.minusmoisturepot3, moisture_minus_cb, LV_EVENT_PRESSED, objects.spinbox3);
    lv_obj_add_event_cb(objects.minusmoisturepot3, moisture_minus_cb, LV_EVENT_LONG_PRESSED_REPEAT, objects.spinbox3);
    lv_obj_clear_flag(objects.spinbox3, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_set_style_text_align(objects.spinbox3, LV_TEXT_ALIGN_CENTER, 0);

    // TEMP
    lv_obj_add_event_cb(objects.plustemp, moisture_plus_cb, LV_EVENT_PRESSED, objects.temp_spinbox);
    lv_obj_add_event_cb(objects.plustemp, moisture_plus_cb, LV_EVENT_LONG_PRESSED_REPEAT, objects.temp_spinbox);
    lv_obj_add_event_cb(objects.minustemp, moisture_minus_cb, LV_EVENT_PRESSED, objects.temp_spinbox);
    lv_obj_add_event_cb(objects.minustemp, moisture_minus_cb, LV_EVENT_LONG_PRESSED_REPEAT, objects.temp_spinbox);
    lv_obj_clear_flag(objects.temp_spinbox, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_set_style_text_align(objects.temp_spinbox, LV_TEXT_ALIGN_CENTER, 0);

    // HUMIDITY
    lv_obj_add_event_cb(objects.plushumidity, moisture_plus_cb, LV_EVENT_PRESSED, objects.humidity_spinbox);
    lv_obj_add_event_cb(objects.plushumidity, moisture_plus_cb, LV_EVENT_LONG_PRESSED_REPEAT, objects.humidity_spinbox);
    lv_obj_add_event_cb(objects.minushumidity, moisture_minus_cb, LV_EVENT_PRESSED, objects.humidity_spinbox);
    lv_obj_add_event_cb(objects.minushumidity, moisture_minus_cb, LV_EVENT_LONG_PRESSED_REPEAT, objects.humidity_spinbox);
    lv_obj_clear_flag(objects.humidity_spinbox, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_set_style_text_align(objects.humidity_spinbox, LV_TEXT_ALIGN_CENTER, 0);

    // POT UPDATE BUTTONS
    lv_obj_add_event_cb(objects.update1, update_pot_cb, LV_EVENT_CLICKED, (void*)1);
    lv_obj_add_event_cb(objects.update2, update_pot_cb, LV_EVENT_CLICKED, (void*)2);
    lv_obj_add_event_cb(objects.update3, update_pot_cb, LV_EVENT_CLICKED, (void*)3);

    // GREENHOUSE UPDATE BUTTON
    lv_obj_add_event_cb(objects.allupdate, allupdate_cb, LV_EVENT_CLICKED, NULL);   
}

// ================= LOOP ==========================
void loop() {
    // Update label colors based on valid data
    for (int i = 0; i < 3; i++) {
        bool valid = !isnan(potsStruct[i].temperature) && !isnan(potsStruct[i].humidity);

        lv_obj_t *tempLabel = nullptr;
        lv_obj_t *humidityLabel = nullptr;

        switch(i) {
            case 0: tempLabel = objects.pot1_temp; humidityLabel = objects.pot1_humidity; break;
            case 1: tempLabel = objects.pot2_temp; humidityLabel = objects.pot2_humidity; break;
            case 2: tempLabel = objects.pot3_temp; humidityLabel = objects.pot3_humidity; break;
        }

        if (valid) {
            lv_obj_set_style_text_color(tempLabel, lv_color_hex(0x000000), LV_PART_MAIN);
            lv_obj_set_style_text_color(humidityLabel, lv_color_hex(0x000000), LV_PART_MAIN);
        } else {
            lv_obj_set_style_text_color(tempLabel, lv_color_hex(0xFF0000), LV_PART_MAIN);
            lv_obj_set_style_text_color(humidityLabel, lv_color_hex(0xFF0000), LV_PART_MAIN);
        }
    }

    lv_timer_handler();
    lv_tick_inc(5);
    delay(5);
}

// ========================= TOUCH =====================================
void touchscreen_read(lv_indev_t *, lv_indev_data_t *data) {

    if (touchscreen.touched()) {
        TS_Point p = touchscreen.getPoint();

        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
        data->point.y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

// ====================== CALLBACKS ====================================
void manualbutton_cb(lv_event_t * e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        loadScreen(SCREEN_ID_MANUAL);
    }
}

void automaticbutton_cb(lv_event_t * e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        loadScreen(SCREEN_ID_MAIN);
    }
}

void homebutton_cb(lv_event_t * e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        loadScreen(SCREEN_ID_SPLASH);
    }
}

void homebuttonman_cb(lv_event_t * e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        loadScreen(SCREEN_ID_SPLASH);
    }
}

void moisture_plus_cb(lv_event_t * e)
{
    lv_obj_t * spin = (lv_obj_t *)lv_event_get_user_data(e);
    lv_spinbox_increment(spin);
}

void moisture_minus_cb(lv_event_t * e)
{
    lv_obj_t * spin = (lv_obj_t *)lv_event_get_user_data(e);
    lv_spinbox_decrement(spin);
}

// ========================== TOLERANCE ================================
float calculateTolerance(float target, float tolerancePercent)
{
    // Returns absolute tolerance value
    return target * (tolerancePercent / 100.0f);
}

// ===================== GET TOLERANCE VALUE ===========================
int getToleranceValue(lv_obj_t * dropdown)
{
    uint16_t selected = lv_dropdown_get_selected(dropdown);

    switch(selected)
    {
        case 0: return 1;  // +/-1%
        case 1: return 3;  // +/-3%
        case 2: return 5;  // +/-5%
        default: return 1;
    }
}

// ===================== UPDATE POT CALLBACK ===========================
void update_pot_cb(lv_event_t * e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;

    uint8_t potNumber = (uint32_t)lv_event_get_user_data(e);

    lv_obj_t * spin = NULL;
    lv_obj_t * dropdown = NULL;

    if (potNumber == 1) {
        spin = objects.spinbox1;
        dropdown = objects.tolerancebox1;
    } else if (potNumber == 2) {
        spin = objects.spinbox2;
        dropdown = objects.tolerancebox2;
    } else if (potNumber == 3) {
        spin = objects.spinbox3;
        dropdown = objects.tolerancebox3;
    }

    moisture_packet_t msp;
    // msp.devAddr = potNumber;                        // which pot to update
    // msp.moisture_target = lv_spinbox_get_value(spin);
    // msp.tolerance = calculateTolerance(msp.moisture_target, getToleranceValue(dropdown));

    esp_now_send(xiaoMAC, (uint8_t*)&msp, sizeof(msp));
}

// ===================== GREENHOUSE UPDATE =============================
void allupdate_cb(lv_event_t * e)
{
    if (lv_event_get_code(e) != LV_EVENT_CLICKED) return;

    status_packet_t packet;
    // packet.type = 2;
    // packet.temp = lv_spinbox_get_value(objects.temp_spinbox);
    // packet.humidity = lv_spinbox_get_value(objects.humidity_spinbox);

    esp_now_send(xiaoMAC, (uint8_t*)&packet, sizeof(packet));
}

// ===================== UPDATED onDataRecv ==========================
void onDataRecv(const uint8_t *, const uint8_t *incomingData, int len) {
    if (len != sizeof(status_packet_t)) return;

    // Copy incoming data into local struct (non-volatile)
    status_packet_t tmp;
    memcpy(&tmp, incomingData, sizeof(tmp));

    int idx = tmp.devAddr - 1;
    if (idx >= 0 && idx < 3) {

        // Store into potsStruct
        potsStruct[idx] = tmp;

        // Compute derived values
        float tempC = (tmp.temperature - 32.0f) * 5.0f / 9.0f;
        float svp = 0.6108f * expf((17.27f * tempC) / (tempC + 237.3f));
        float vpd = svp * (1.0f - tmp.humidity / 100.0f);

        // Update UI
        switch(idx) {
            case 0:
                lv_label_set_text_fmt(objects.pot1_temp, "%.1f °F / %.1f °C", tmp.temperature, tempC);
                lv_label_set_text_fmt(objects.pot1_humidity, "%.1f %%", tmp.humidity);
                lv_label_set_text_fmt(objects.pot1_moisture, "%.1f %%", tmp.soil_moisture);
                lv_label_set_text_fmt(objects.pot1_vpd, "%.2f kPa", vpd);
                break;

            case 1:
                lv_label_set_text_fmt(objects.pot2_temp, "%.1f °F / %.1f °C", tmp.temperature, tempC);
                lv_label_set_text_fmt(objects.pot2_humidity, "%.1f %%", tmp.humidity);
                lv_label_set_text_fmt(objects.pot2_moisture, "%.1f %%", tmp.soil_moisture);
                lv_label_set_text_fmt(objects.pot2_vpd, "%.2f kPa", vpd);
                break;

            case 2:
                lv_label_set_text_fmt(objects.pot3_temp, "%.1f °F / %.1f °C", tmp.temperature, tempC);
                lv_label_set_text_fmt(objects.pot3_humidity, "%.1f %%", tmp.humidity);
                lv_label_set_text_fmt(objects.pot3_moisture, "%.1f %%", tmp.soil_moisture);
                lv_label_set_text_fmt(objects.pot3_vpd, "%.2f kPa", vpd);
                break;
        }
    }

    Serial.println("=== NEW STATUS RECEIVED ===");
    Serial.print("DevAddr: "); Serial.println(tmp.devAddr);
}