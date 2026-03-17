#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "DHT.h"

// ================= DEVICE DEFINES =================
#define DEVICE_ADDR 1
#define DEVICE_TYPE_XIAO 0x01

// ================= MAC ADDRESSES =================
// REPLACE with your CYD MAC
uint8_t cydMAC[] = {0x5C, 0x01, 0x3B, 0x50, 0x11, 0xD0}; //5C:01:3B:50:11:D0
// uint8_t pumpMAC[] = {0x, 0x, 0x, 0x, 0x, 0x};

// ================= COMMAND DEFINES =================
// #define CMD_VALVE1  1
// #define CMD_VALVE2  2
// #define CMD_VALVE3  3

// ================= VARIABLES ==================
uint8_t moisture_set =0;
float t,h,m =0;
uint8_t sendCount =0;

// ================= PINS =================
#define DHTPIN D1
#define DHTTYPE DHT22

const int valvePin = D3;
// const int valve2Pin = D5;
// const int valve3Pin = D6;
const int moisturePin = A2;
// const int lightPin = D10;

DHT dht(DHTPIN, DHTTYPE);

// ================= PACKETS =================
typedef struct __attribute__((packed)) {
    uint8_t set;
} moisture_packet_t;

moisture_packet_t msp;

typedef struct __attribute__((packed)) {
    uint8_t devAddr;
    uint8_t devType;
    uint8_t valve_state;
    float temperature;
    float humidity;
    float soil_moisture;

} status_packet_t;

status_packet_t txData;

typedef struct __attribute__((packed)) {
    uint8_t devAddr;
    uint8_t valve_state;
} valve_packet_t;

valve_packet_t valveState;

// ================= RECEIVE COMMAND =================
void onDataRecv(const uint8_t *, const uint8_t *data, int len) {

    if (len != sizeof(moisture_packet_t)) return;

    memcpy(&msp, data, len);

    // if (cmd.targetAddr != DEVICE_ADDR) return;

    if (msp.set != moisture_set)
        moisture_set=msp.set;
    // if (cmd.command == CMD_VALVE2)
    //     digitalWrite(valve2Pin, cmd.value ? HIGH : LOW);
    // if (cmd.command == CMD_VALVE3)
    //     digitalWrite(valve3Pin, cmd.value ? HIGH : LOW);
    Serial.print(moisture_set);
    Serial.print(" = ");
    Serial.println(msp.set);
    delay(1000);
}
// =================== SEND COMMAND ================
void sendStatusData() {
    txData.devAddr = DEVICE_ADDR;
    txData.devType = DEVICE_TYPE_XIAO;
    txData.valve_state = digitalRead(valvePin);
    txData.temperature = t;
    txData.humidity = h;
    txData.soil_moisture = m;

    esp_now_send(cydMAC, (uint8_t*)&txData, sizeof(txData));
}

// void sendValveData() {
//     valveState.devAddr = DEVICE_ADDR;
//     valveState.valve_state = digitalRead(valvePin);

//     esp_now_send(pumpMAC, (uint8_t*)&valveState,sizeof(valveState));
// }
// ================= SETUP =================
void setup() {
    Serial.begin(9600);
    delay(100);
    // Serial.println("Yo");
    // delay(1000);
    WiFi.mode(WIFI_STA);

    dht.begin();

    pinMode(valvePin, OUTPUT);

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
    h = dht.readHumidity();
    t = dht.readTemperature(true);
    m=analogRead(moisturePin);
    delay(100);

    // Converitng reading to 0-100 scale
    // For moisture Saturation (%)
    m=1-((m-1600)/2495);
    delay(100);

    // Check if moisture is within range
    // And sending an update to pump on valve state change
    // if (m< (moisture_set-5)){
    //     digitalWrite(valvePin, HIGH);
    //     sendValveData();
    // }
    // else if (m> (moisture_set+5)){
    //     digitalWrite(valvePin, LOW);
    //     sendValveData();
    // }
    
    delay(300);

    // Counting loop for sending every 10 Cycles or 5 seconds
    if (sendCount == 9){
        sendStatusData();
        sendCount=0;
        // Checking values from the sensor
        // Serial.println(moisture_set);
        // Serial.println(h);
        // Serial.println(t);
        // Serial.println(m);
        // Serial.println("");
    }
    else {
        sendCount += 1;
    }
    // Serial.println(sendCount);
}





//MAC OBTAINED
// #include <Arduino.h>
// #include <WiFi.h>

// void setup() {
//   Serial.begin(9600);
//   delay(2000);  // wait for Serial to attach

//   Serial.println("START TEST");
// }

// void loop() {
//   Serial.print("WiFi Status: ");
//   Serial.println(WiFi.status());  // check Wi-Fi stack

//   Serial.print("MAC: ");
//   Serial.println(WiFi.macAddress());  // should print

//   delay(2000);
// }







//OLD
// //************************************************************************************
// //* ESP Now Sensor XIAO ESP32-C3                                   
// //* Author: T2                                                                       
// //* Company: T2Elektroteknik                                                         
// //* Date: 10/04/25                                                                  
// //* Description: Baseline Sensor initiator/sender       
// //* CPU: XIAO ESP32-C3                                                                     
// //************************************************************************************
// #include <Arduino.h>
// #include "DHT.h"
// #include <WiFi.h>
// #include "esp_now.h"

// #define DHTPIN D2       // Digital pin connected to the DHT sensor
// #define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// const int lightSensorPin = A0;
// const int motorPin1 = 21;
// const int motorPin2 = 7;
// const int moisturePin = 3;

// DHT dht(DHTPIN, DHTTYPE);

// // ESP Now Settings
// // MAC Address of responder - edit as required
// uint8_t broadcastAddress[] = {0x14, 0x33, 0x5C, 0x6B, 0xA8, 0x68};

// #define DEVICE_ADDR 1 //<< Address you are assigning to this device
// #define DEVICE_TYPE 0x01 //<< Device ID Temp/Humidity
 
// // Define a data structure
// typedef struct __attribute__((packed)) {
//   uint8_t devAddr;
//   uint8_t devType;
//   float humidity;
//   float temperature;
// } struct_message;
 
// // Create a structured object
// struct_message myData;
 
// // Peer info
// esp_now_peer_info_t peerInfo;

// // Function Prototypes
// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

 
// /////////////////////////////////////////////////////////////////////////////
// // Setup Function
// /////////////////////////////////////////////////////////////////////////////
// void setup() {
//   Serial.begin(9600);
//   Serial.println(F("DHTxx test!"));
  
//   dht.begin();

//     // Set ESP32 as a Wi-Fi Station
//   WiFi.mode(WIFI_STA);
 
//   // Initilize ESP-NOW
//   if (esp_now_init() != ESP_OK) {
//     Serial.println("Error initializing ESP-NOW");
//     return;
//   }
//   // Motor Setup
//   pinMode(motorPin1, OUTPUT);
//   pinMode(motorPin2, OUTPUT);
//   digitalWrite(motorPin1,LOW);
//   digitalWrite(motorPin2,LOW);

//   // Moisture Sensor Input
//   pinMode(moisturePin, INPUT);
//   // Light Sensor
//   pinMode(lightSensorPin, INPUT);
//   // Register the send callback
//   esp_now_register_send_cb(OnDataSent);
  
//   // Register peer
//   memcpy(peerInfo.peer_addr, broadcastAddress, 6);
//   peerInfo.channel = 0;  
//   peerInfo.encrypt = false;
  
//   // Add peer        
//   if (esp_now_add_peer(&peerInfo) != ESP_OK){
//     Serial.println("Failed to add peer");
//     return;
//   }
// }

// /////////////////////////////////////////////////////////////////////////////
// // Loop Forever
// /////////////////////////////////////////////////////////////////////////////
// void loop() {
  
//   float h = dht.readHumidity();
//   // Read temperature as Celsius (the default)
//   float t = dht.readTemperature();
//   // Read temperature as Fahrenheit (isFahrenheit = true)
//   float f = dht.readTemperature(true);
//   // Read light sensor data
//   int lightValue = analogRead(lightSensorPin);
//   // Read Soil Moisture
//   int moisture = analogRead(moisturePin);
//   // Turn On Motor
//   if (f > 74) {
//     digitalWrite(motorPin1, HIGH);
//     digitalWrite(motorPin2, LOW);
//     Serial.println("Motor ON");
//   }
//   // Turn Off Motor
//   else{
//   digitalWrite(motorPin1, LOW);
//   digitalWrite(motorPin2, LOW);
//   Serial.println("Motor OFF");
//   }
//   // Check if any reads failed and exit early (to try again).
//   if (isnan(h) || isnan(t) || isnan(f)) {
//     Serial.println(F("Failed to read from DHT sensor!"));
//     return;
//   }
//   Serial.print(F("Humidity: "));
//   Serial.print(h);
//   Serial.print(F("%  Temperature: "));
//   Serial.print(f);
//   Serial.println(F("°F "));
//   Serial.print(F("Light: "));
//   Serial.println(lightValue);
//   Serial.print(F("Soil Moisture: "));
//   Serial.println(moisture);

//   myData.devAddr = DEVICE_ADDR;
//   myData.devType = DEVICE_TYPE;
//   myData.humidity = h;
//   myData.temperature = f;

//   // Send message via ESP-NOW
//   esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
//   if (result == ESP_OK) {
//     Serial.println("Sending confirmed");
//   }
//   else {
//     Serial.println("Sending error");
//   }
  
//   // Wait a few seconds between measurements.
//   delay(2000);
// }


// // Callback function called when data is sent
// void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
//   Serial.print("\r\nLast Packet Send Status:\t");
//   Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
// }