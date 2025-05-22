# Project Purpose

This repository contains the documentation and, eventually, the code for a system designed to collect sensor data from ESP8266-based sensor nodes using the ESP-NOW communication protocol. The collected data is then relayed via an ESP32 serial bridge and a Python application to an MQTT broker, making it available for various IoT applications.

# System Architecture

This document describes the architecture of the IoT sensor network.

## Components

The system consists of the following main components:

1.  **ESP8266 Sensors:** These are microcontroller-based sensors responsible for collecting data from the environment (e.g., temperature, humidity).
2.  **ESP32 Serial Bridge:** This microcontroller acts as a bridge between the ESP8266 sensors and the MQTT broker. It receives data from the sensors and forwards it to the broker.
3.  **Python MQTT Broker:** This is a central server that receives data from the ESP32 serial bridge and makes it available to other clients that subscribe to specific topics.

## Interactions and Protocols

The components interact as follows:

1.  **ESP8266 Sensors to ESP32 Serial Bridge (ESP-NOW):**
    *   The ESP8266 sensors collect data.
    *   They transmit this data to the ESP32 serial bridge using the **ESP-NOW** protocol. ESP-NOW is a connectionless Wi-Fi communication protocol developed by Espressif, allowing direct communication between ESP devices without needing a traditional Wi-Fi network or router. This is suitable for low-power, short-distance communication.

2.  **ESP32 Serial Bridge to Python MQTT Broker (Serial and MQTT):**
    *   The ESP32 serial bridge receives data from the ESP8266 sensors via ESP-NOW.
    *   The ESP32 is connected to a machine running the Python MQTT broker (likely via a USB cable, providing a **Serial** connection).
    *   A Python script running on the machine reads the data from the serial port.
    *   This script then publishes the received data to the **Python MQTT Broker** using the **MQTT** protocol. MQTT (Message Queuing Telemetry Transport) is a lightweight, publish-subscribe network protocol ideal for IoT applications due to its low bandwidth requirements and efficient data distribution.

3.  **Python MQTT Broker to Clients (MQTT):**
    *   Other applications or clients can subscribe to specific topics on the MQTT broker.
    *   When data is published to a topic by the ESP32 bridge (via the Python script), the broker forwards this data to all subscribed clients.

## Data Flow Summary

Environment -> ESP8266 Sensors --(ESP-NOW)--> ESP32 Serial Bridge --(Serial)--> Python Script on Host Machine --(MQTT)--> Python MQTT Broker --(MQTT)--> Subscribed Clients

## Advantages of this Architecture

*   **Low Power Sensor Operation:** ESP-NOW allows ESP8266 sensors to send data quickly and then return to a deep sleep state, conserving battery.
*   **Decoupling:** MQTT broker decouples data producers (sensors) from data consumers (clients).
*   **Scalability:** New sensors or client applications can be easily added to the system.
*   **Flexibility:** Different types of sensors and client applications can be integrated as long as they support the defined protocols.
