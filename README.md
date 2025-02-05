# Smart Irrigation System

## Description

This is a Smart Irrigation System that monitors soil moisture, ambient temperature, and humidity. It uses a DHT22 sensor for reading temperature and humidity, and a soil moisture sensor to determine the moisture level of the soil. Based on these readings, a relay is used to control a pump, turning it on or off based on specific conditions.

The system also displays these readings on an LCD screen and sends them to the serial monitor for debugging and monitoring.

## Components Used

- **DHT22 Sensor**: Measures the ambient temperature and humidity.
- **Soil Moisture Sensor**: Measures the moisture content in the soil.
- **Relay Module**: Used to control a pump to water the plants.
- **LiquidCrystal I2C 16x2 LCD**: Displays sensor readings and pump status.

## Pin Configuration

- **DHT22**: Pin 27
- **Soil Moisture Sensor**: Pin 33
- **Relay**: Pin 4
- **LCD I2C**: Address `0x27`, 16x2 screen

## Setup

1. Connect the DHT22 sensor to pin 27.
2. Connect the soil moisture sensor to pin 33.
3. Connect the relay to pin 4.
4. Connect the LCD display via I2C with address `0x27`.
5. Upload the code to your microcontroller.

## Working

- The system reads temperature, humidity, and soil moisture every 2 seconds.
- If the soil moisture drops below 30% and the temperature is under 30°C, the pump is turned on to irrigate the plants.
- The pump will turn off if the soil moisture is sufficient or if the temperature exceeds 30°C.
- The LCD displays the temperature, soil moisture, and the status of the pump.
- The serial monitor also shows the current readings for debugging purposes.

## Future Improvements

- Add WiFi capabilities to send data to a cloud service for remote monitoring.
- Implement a web interface to control the irrigation system manually.
- Add more sensors for environmental data (e.g., light level, rainfall).
