#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <ArduinoJson.h>

uint8_t  fixedAddress[]      = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};



typedef struct struct_message {
  int     mesh_id;
  uint8_t sensor_id[6];
  int  type;
  float   state;
  float   temperature;
  float   humidity;
  float   moisture;
  float   battery;
} struct_message;



void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&msg, incomingData, sizeof(msg));
  char macAddr[18];
  sprintf(macAddr, "%02X%02X%02X%02X%02X%02X", msg.sensor_id[0], msg.sensor_id[1], msg.sensor_id[2], msg.sensor_id[3], msg.sensor_id[4], msg.sensor_id[5]);


  StaticJsonDocument<256> doc;
  doc["ID"] = (macAddr);
  doc["type"] = (msg.type);
  doc["state"] = (msg.state);
  doc["temperature"] = (msg.temperature);
  doc["battery"] = (msg.battery);
  doc["humidity"] = (msg.humidity);
  doc["moisture"] = (msg.moisture);

// Serial.println();

  serializeJson(doc, Serial);

}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  esp_wifi_set_mac(WIFI_IF_STA, &fixedAddress[0]);
 // WiFi_set_macaddr(STATION_IF, &fixedAddress[0]);
  Serial.println(WiFi.macAddress());
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}
