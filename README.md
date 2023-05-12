# ESPNow2MQTT
ESP-Now to MQTT broker

## The project parts
The project consist of
- ESPNOW sensors (DS18B20 or DHT22)
- ESPNOW-Serial that connects via a serial port to a python broker that forwards the messages to a MQTT broker.
- Python broker
- A computer (Ex a Raspberry Pi) that can run Python 3.6 and forwards the MQTT messages to a MQTT Broker

## Information flow
Device (ESP8266) --- (ESP-NOW) --- ESPNOW_Serial --- (serial) --- Python Broker --- (IP) --- MQTT Broker
