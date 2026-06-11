# Smart-Environmental-Agriculture-Monitoring-System
IoT-based smart agriculture monitoring and automated irrigation system using ESP8266, Blynk Cloud, DHT22, Soil Moisture Sensor, LDR, and MQ135.

# Overview
This project monitors environmental and agricultural conditions in real time using multiple sensors connected to an ESP8266 microcontroller. Sensor data is transmitted to the Blynk Cloud platform, allowing remote monitoring through a smartphone dashboard.

The system also implements automatic irrigation logic based on soil moisture, light intensity, temperature, and humidity conditions to improve water efficiency and support smart farming applications.

Features
- Real-time environmental monitoring via Blynk
- Soil moisture measurement
- Temperature and humidity monitoring
- Light intensity detection
- Air quality monitoring
- Automatic irrigation control using relay and water pump
- Remote dashboard access through smartphone
- Notification system for abnormal conditions

# Hardware Components

| Component | Description |
|-----------|-------------|
| ESP8266 NodeMCU | Main microcontroller with WiFi connectivity |
| DHT22 | Temperature and humidity sensor |
| Soil Moisture Sensor | Soil moisture monitoring |
| LDR | Light intensity sensor |
| MQ135 | Air quality sensor |
| Relay Module | Automatic pump control |
| Water Pump | Irrigation actuator |

<img width="752" height="362" alt="Block Diagram" src="https://github.com/user-attachments/assets/a2040a98-aa62-4b7d-a678-bf74bfc54137" />

# Decision Logic
The irrigation system uses a multi-sensor decision approach:
- Soil moisture acts as the primary parameter.
- Light intensity determines whether irrigation should be delayed.
- Temperature and humidity strengthen irrigation decisions during hot conditions.
- Air quality monitoring generates alerts but does not affect irrigation.

Emergency mode is activated when:
- Soil moisture ≤ 20%
- Temperature > 35°C
- Humidity < 30%

Under these conditions, irrigation is forced to prevent plant stress.

# Results
The system successfully:
- Transmitted sensor data to Blynk in real time.
- Monitored environmental conditions remotely.
- Activated irrigation automatically based on environmental conditions.
- Generated notifications for poor air quality and extreme weather conditions.

Technologies Used
- ESP8266
- Arduino IDE
- Blynk IoT
- Embedded C++
- IoT
- WiFi Communication

Project Demonstration
Demo Video: https://drive.google.com/file/d/1iTzus8E506-PxS8fr3ateA_ZEAg26j0V/view?usp=sharing 

# Author
- Naufal Arya Pradipta 235150300111028
- Adhitya Noer Effendi 235150307111024
- Fadlan Umar Rozikin 235150307111032
