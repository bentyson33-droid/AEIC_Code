#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

// ================= DEVICE DEFINES =================
// Address of Screen is 0
// Pots are 1, 2, and 3
#define DEVICE_ADDR 4
#define DEVICE_TYPE_XIAO 0x01

// ================= MAC ADDRESSES =================
// REPLACE with your CYD MAC
uint8_t cydMAC[] = {0x14, 0x33, 0x5C, 0x6B, 0xA8, 0x68}; //5C:01:3B:50:11:D0

// ================= COMMAND DEFINES =================

// ================= VARIABLES ==================
float avg_temp = 65;
float avg_humid = 50;
float water_level = 50;
int sendCount = 0;
boolean override =0;
int lightLevel =255;
int fanLevel =0;
boolean humidState =0;
boolean pumpState =0;
long duration;
float distance;
uint8_t lightCount =0;
uint8_t lightTime =8;
uint8_t lightOFF =0;
// ================= PINS =================
#define fanPin A0
#define lightPin A1
#define pumpPin D2
#define humidifierPin D3
#define waterlevelEcho D6
#define waterlevelTrig D9
// ================= PACKETS =================
// Packet from Sceen with User Set Points
typedef struct __attribute__((packed)) {
    uint8_t temp_set;
    uint8_t humid_set;
    int temp_DB;
    int humid_DB;
    boolean override;
    // uint8_t lightTime;
} set_packet_t;
set_packet_t setPoints;

// Data points sent to Screen
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

// Packet for Manual Mode from Screen
typedef struct __attribute__((packed)) {
    uint8_t devAddr;
    boolean override;
    boolean humidState;
    boolean pumpState;
    uint8_t lightLevel;
    uint8_t fanLevel;
} manual_packet_t;
manual_packet_t manualMode;

// Packet from Pots to Pump
typedef struct __attribute__((packed)) {
    uint8_t devAddr;
    uint8_t valve_state;
    float temp;
    float humidity;
} sensor_packet_t;
// Temporary Packet to set values
sensor_packet_t SensorData;
// Creating Packets for each pot
sensor_packet_t pot1;
sensor_packet_t pot2;
sensor_packet_t pot3;

// Put all 3 in a structure
sensor_packet_t potData[3] = {pot1, pot2, pot3};

// ================= RECEIVE COMMAND =================
void onDataRecv(const uint8_t *, const uint8_t *data, int len) {
  Serial.println("message recieved");
  Serial.println(" ");
    // Checking which packet has been recieved
    if (len == sizeof(set_packet_t)){
      // Copy incoming data to memory packet of set points
      memcpy(&setPoints, data, len);
      // Overwriting variables to reset the loop
      // As if the device just powered on
      // lightTime = setPoints.lightTime;
      lightLevel = 255;
      // lightCount = 0;
      override = setPoints.override;
      Serial.print(setPoints.temp_DB);
      Serial.print(" and ");
      Serial.println(setPoints.temp_set);
    }
    if (len == sizeof(sensor_packet_t)){
      // Copy Data to memory packet
      memcpy(&SensorData, data, len);
      // Set the values in the sturctures to the new values
      potData[SensorData.devAddr-1].humidity = SensorData.humidity;
      potData[SensorData.devAddr-1].temp = SensorData.temp;
      potData[SensorData.devAddr-1].valve_state = SensorData.valve_state;
    }
    if (len == sizeof(manual_packet_t)){
      memcpy(&manualMode, data, len);
      override = manualMode.override;
      digitalWrite(humidifierPin, manualMode.humidState);
      digitalWrite(pumpPin, manualMode.pumpState);
      analogWrite(fanPin, manualMode.fanLevel);
      analogWrite(lightPin, manualMode.lightLevel);
      Serial.println("Override Set");
    }
    delay(100);
}
// =================== SEND COMMAND ================
// Sending Data to Screen
void sendStatusData() {
  // Setting values in Packet going to Screen
  txData.devAddr = DEVICE_ADDR;
  txData.devType = DEVICE_TYPE_XIAO;
  txData.fan_state = fanLevel;
  txData.pump_state = digitalRead(pumpPin);
  txData.humidifier_state = digitalRead(humidifierPin);
  txData.light_level = lightLevel;
  txData.water_level = water_level;
  // Sending to Screen 
  esp_now_send(cydMAC, (uint8_t*)&txData, sizeof(txData));
}

// ================= SETUP =================
void setup() {
    Serial.begin(9600);
    delay(100);
    // Serial.println("Yo");
    // delay(1000);
    WiFi.mode(WIFI_AP_STA);

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
    // Adding the Screen so it can send info
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, cydMAC, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    esp_now_add_peer(&peerInfo);
}

// ================= LOOP =================
void loop() {
  if (override == 1){
    delay(100);
    return;
  }
  else {
    analogWrite(lightPin, lightLevel);
    analogWrite(fanPin, fanLevel);

    // Delays are set so loop runs every 500 milliseconds
    delay(99.988); 

    // Clear the trigPin by setting it LOW
    digitalWrite(waterlevelTrig, LOW);
    delayMicroseconds(2);
  
    // Trigger the sensor by sending a 10 microsecond pulse
    digitalWrite(waterlevelTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(waterlevelTrig, LOW);
  
    // Read the echoPin; pulseIn returns the duration in microseconds
    duration = pulseIn(waterlevelEcho, HIGH);
  
    // Calculate distance: (time * speed of sound) / 2
    // Speed of sound is ~0.0343 cm/µs
    distance = (duration * 0.0343) / 2;
  
    // Serial.println(distance);
    // empty = 16 cm
    // full = 8 cm
    water_level = (1 - (distance - 8)/8)*100;
    Serial.println(water_level);
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
    if (avg_temp > setPoints.temp_set + setPoints.temp_DB & fanLevel != 255){
      fanLevel = 255;
    }
    else if (avg_temp < setPoints.temp_set - setPoints.temp_DB & fanLevel != 0){
      fanLevel = 0;
    }
  // Chekcing Humidity to turn on/off humidifer
    if ((avg_humid < setPoints.humid_set - setPoints.humid_DB) & (water_level > 10)){
      digitalWrite(humidifierPin, HIGH);
    }
    else if ((avg_humid > setPoints.humid_set + setPoints.humid_DB) || (water_level < 10)){
      digitalWrite(humidifierPin, LOW);
    }
    delay(300);


  // Turning the pump on if any valve is open
    if (potData[0].valve_state==1 ||
        potData[1].valve_state==1 ||
        potData[2].valve_state==1){
          digitalWrite(pumpPin, HIGH);
    }
    else {
      digitalWrite(pumpPin, 0);
    }


    // Counting loop for sending every 10 Cycles or 5 seconds
    if (sendCount == 9){
        sendStatusData();
        sendCount=0;
    }
    else {
        sendCount += 1;
    }
    Serial.println(sendCount);

    // // Light Check
    // // Converts cycles to seconds to minutes to hours
    // // Checks whether light is on or off
    // // If "ON" checks how long it has been on
    // // If "OFF" how long it has been off
    // if (lightLevel == 255){
    //   if (lightCount*2*60 == (lightTime)*2*60*60){
    //     lightLevel = 0;
    //     lightOFF = 0;
    //   }
    //   else {lightCount = lightCount + 1;}
    // }
    // else if (lightLevel == 0){
    //   if (lightOFF == (24-lightTime)*2*60*60){
    //     lightLevel = 255;
    //     lightCount = 0;
    //   }
    //   else {lightOFF = lightOFF + 1;}
    // }
  }
}