#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

// ================= DEVICE DEFINES =================
#define DEVICE_ADDR 4
#define DEVICE_TYPE_XIAO 0x01

// ================= MAC ADDRESSES =================
// REPLACE with your CYD MAC
uint8_t cydMAC[] = {0x5C, 0x01, 0x3B, 0x50, 0x11, 0xD0}; //5C:01:3B:50:11:D0

// ================= COMMAND DEFINES =================

// ================= VARIABLES ==================
float temp_set = 65;
float humid_set = 50;
float avg_temp = 65;
float avg_humid = 50;
uint8_t water_level = 50;
int sendCount = 0;
// ================= PINS =================
#define fanPin A0
#define lightPin A1
#define pumpPin A2
#define humidifierPin D4
#define waterlevelEcho D7
#define waterlevelTrig D10
// ================= PACKETS =================
typedef struct __attribute__((packed)) {
    uint8_t temp_set;
    uint8_t humid_set;
} set_packet_t;

set_packet_t setPoints;

typedef struct __attribute__((packed)) {
    uint8_t devAddr;
    uint8_t devType;
    int fan_state;
    int pump_state;
    boolean humidifier_state;
    int light_level;
    float water_level;
} status_packet_t;

status_packet_t txData;

typedef struct __attribute__((packed)) {
    uint8_t devAddr;
    uint8_t valve_state;
    float temp;
    float humidity;
} sensor_packet_t;

sensor_packet_t SensorData;
// Creating Packets for each pot
sensor_packet_t pot1;
sensor_packet_t pot2;
sensor_packet_t pot3;

// Put all 3 in a structure
sensor_packet_t potData[3] = {pot1, pot2, pot3};

// ================= RECEIVE COMMAND =================
void onDataRecv(const uint8_t *, const uint8_t *data, int len) {

    if (len == sizeof(set_packet_t)){

      memcpy(&setPoints, data, len);

      // if (cmd.targetAddr != DEVICE_ADDR) return;

      if (setPoints.temp_set != temp_set){
          temp_set=setPoints.temp_set;
      }
      if (setPoints.humid_set != humid_set){
          humid_set=setPoints.humid_set;
      }
      // Serial.print(temp_set);
      // Serial.print(" = ");
      // Serial.println(tsp.set);
    }
    if (len == sizeof(sensor_packet_t)){
      // Copy Data to memory
      memcpy(&SensorData, data, len);
      // Set the values in the sturctures to the new values
      potData[SensorData.devAddr-1].humidity = SensorData.humidity;
      potData[SensorData.devAddr-1].temp = SensorData.temp;
      potData[SensorData.devAddr-1].valve_state = SensorData.valve_state;
    }

    delay(1000);
}
// =================== SEND COMMAND ================
void sendStatusData() {
    txData.devAddr = DEVICE_ADDR;
    txData.devType = DEVICE_TYPE_XIAO;
    txData.fan_state = analogRead(fanPin);
    txData.pump_state = analogRead(pumpPin);
    txData.humidifier_state = digitalRead(humidifierPin);
    txData.light_level = analogRead(lightPin);
    txData.water_level = 50;

    esp_now_send(cydMAC, (uint8_t*)&txData, sizeof(txData));
}

// ================= PWM Command =========================
void pwm(uint8_t outputPin, uint32_t frequency, float dutyCycle) {
  for(;;){
    pinMode(outputPin, HIGH);
    delay((1/frequency)*dutyCycle);
    pinMode(outputPin, LOW);
    delay((1/frequency)*(1-dutyCycle));
  }
}

// ================= SETUP =================
void setup() {
    Serial.begin(9600);
    delay(100);
    // Serial.println("Yo");
    // delay(1000);
    WiFi.mode(WIFI_STA);

    pinMode(fanPin, OUTPUT);
    pinMode(lightPin, OUTPUT);
    pinMode(pumpPin, OUTPUT);
    pinMode(humidifierPin, OUTPUT);
    pinMode(waterlevelTrig, OUTPUT);
    pinMode(waterlevelEcho, INPUT);

    if (esp_now_init() != ESP_OK) {
        Serial.println("ESP-NOW init failed");
        return;
    }

    esp_now_register_recv_cb(onDataRecv);

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, cydMAC, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    esp_now_add_peer(&peerInfo);
}

// ================= LOOP =================
void loop() {
  delay(100);
  
  // Finding average temp & humidity
  avg_temp = 0;
  avg_humid = 0;
  for (int i=0; i<3; i++){
    avg_temp = avg_temp + potData[i].temp;
    avg_humid = avg_humid + potData[i].humidity;
  }
  avg_temp=avg_temp/3;
  avg_humid=avg_humid/3;
  delay(100);
// Checking Temp to turn on/off fan
  if (avg_temp > temp_set + 5){
    pinMode(fanPin, HIGH);
  }
  else if (avg_temp < temp_set + 5){
    pinMode(fanPin, LOW);
  }
// Chekcing Humidity to turn on/off humidifer
  if (avg_humid < humid_set + 5){
    pinMode(humidifierPin, HIGH);
  }
  if (avg_humid > humid_set + 5){
    pinMode(humidifierPin, LOW);
  }
  delay(300);
// Turning the pump on if any valve is open
  if (potData[0].valve_state==1 ||
      potData[1].valve_state==1 ||
      potData[2].valve_state==1){
        analogWrite(pumpPin, 255);
  }
  else {
    analogWrite(pumpPin, 0);
  }

  // Counting loop for sending every 10 Cycles or  seconds
  if (sendCount == 9){
      sendStatusData();
      sendCount=0;
  }
  else {
      sendCount += 1;
  }
  // Serial.println(sendCount);
}
