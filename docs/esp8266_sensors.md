# ESP8266 Sensor Functionality

This document details the functionality of the ESP8266-based sensor nodes within the IoT network.

## Overview

The primary role of the ESP8266 sensor units is to periodically measure environmental data, specifically temperature and humidity, and transmit this information wirelessly to the ESP32 serial bridge. They are designed for low-power operation to maximize battery life.

## Sensor Hardware

Each ESP8266 unit is typically interfaced with one of the following sensor types:

*   **DHT22 (or AM2302):** A digital sensor that measures both temperature and humidity. It's known for its accuracy and ease of use.
*   **DS18B20:** A digital temperature sensor that uses a 1-Wire communication protocol. Multiple DS18B20 sensors can be connected on a single data line. While primarily for temperature, humidity sensing would require an additional sensor if using DS18B20s exclusively.

The choice of sensor depends on the specific requirements of the deployment, such as accuracy, cost, and whether humidity measurement is needed.

## Data Acquisition and Transmission

1.  **Wake Up:** The ESP8266 wakes up from its deep sleep cycle.
2.  **Sensor Reading:** It actively powers and reads data from the connected sensor (DHT22 or DS18B20).
    *   For DHT22, it reads both temperature and humidity.
    *   For DS18B20, it reads temperature.
3.  **Data Transmission (ESP-NOW):**
    *   Once the data is acquired, the ESP8266 formats it into a small packet.
    *   It then transmits this packet to the designated ESP32 serial bridge using the **ESP-NOW** protocol. ESP-NOW is chosen for its speed and low power consumption, as it allows the ESP8266 to send data without the overhead of a full Wi-Fi connection (association, authentication, etc.).
    *   The ESP8266 will typically have the MAC address of the ESP32 bridge hardcoded or configured to know where to send the data.

## Power Saving (Sleep Cycle)

To achieve long operational life on battery power, the ESP8266 units employ a deep sleep mechanism:

1.  **Active Mode:** The ESP8266 is active only for a very short period – just long enough to wake up, read the sensor, and transmit the data. This active period is typically a few seconds.
2.  **Deep Sleep Mode:** After successfully transmitting the data (or after a timeout/failure condition), the ESP8266 enters deep sleep mode. In this mode, most of its components are powered down, drastically reducing power consumption (to the order of microamperes).
3.  **Wake-up Trigger:** The ESP8266 is configured to wake up automatically after a predefined interval (e.g., every 5, 10, or 30 minutes). This is usually managed by its internal Real-Time Clock (RTC) and a timer.

This cycle of waking, sensing, transmitting, and sleeping allows the ESP8266 sensors to operate for extended periods (months or even years) on a single battery, depending on the sleep duration and battery capacity.
