

//#define DEBUG_FLAG            // uncomment to show debug info

#define SDS18B20    // pick one
//#define SDHT22    // pick one

#include <ESP8266WiFi.h>
#include <espnow.h>
#ifdef SDHT22
#include <DHT.h>
#endif
#ifdef SDS18B20
#include <OneWire.h>
#include <DallasTemperature.h>
#endif


#define sensorType 1 // 1 = sensor 2 = switch
#define MESH_ID 6734922
#define GROUP_SWITCH   1
#define GROUP_HT       2


#define   donePin      4
#define   sensorPin    5
#define   ledPin       2

byte      espnow_attemps = 3;
uint8_t   receiverAddress[]      = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};
unsigned long     start_time;
bool      ack_received;


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

struct_message msg;
#ifdef SDHT22
DHT       dht(sensorPin, DHT22);
#endif

#ifdef SDS18B20
OneWire oneWire(sensorPin);
DallasTemperature sensors(&oneWire);
#endif


void setup() {

//  digitalWrite(donePin, HIGH);
//  pinMode(donePin, OUTPUT);

#ifdef SDHT22
  dht.begin();
#endif
#ifdef SDS18B20
  sensors.begin();
#endif
  start_time = millis();
  ack_received = false;

#ifdef DEBUG_FLAG
  Serial.begin(115200);
#endif

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  while (esp_now_init() != 0) {
#ifdef DEBUG_FLAG
    Serial.println("Error initializing ESP-NOW, retrying ...");
#endif
    delay(10);
    if (espnow_attemps-- <= 0) gotoSleep();
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(receiverAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
  esp_now_register_send_cb(OnDataSent);
  sendReading();

}


void loop() {

  if ( ack_received == true)   gotoSleep();
}

void sendReading() {

  msg.mesh_id = MESH_ID;
  //msg.category =  GROUP_HT;
  WiFi.macAddress(msg.sensor_id);
#ifdef SDHT22
  while ( millis() - start_time < 2000 ) {}
  msg.temperature =  dht.readTemperature();
  msg.humidity =  dht.readHumidity();
#endif
#ifdef SDS18B20
  sensors.requestTemperatures();
  msg.temperature = sensors.getTempCByIndex(0);
  msg.humidity =  0;
#endif

#ifdef Soil
  msg.moisture =  analogRead(A0);
  if ( moistureMin < msg.moisture  ) {
    moistureMin = msg.moisture; // Record the lowest value
  }
  if ( msg.moisture <  moistureMax ) {
    moistureMax = msg.moisture; // Record the lowest value
  }
  msg.type = (sensorType);
#endif


  //msg.battery = 0;   // using 3.3M & 1M voltage divider
  esp_now_send(receiverAddress, (uint8_t *) &msg, sizeof(msg));
}

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {

  ack_received = true;
}

void gotoSleep() {

  delay(60000);
  ESP.reset();
  //ESP.deepSleep(0);
}
