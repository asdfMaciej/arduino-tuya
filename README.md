# Controlling Tuya lights with Arduino Uno and ESP8266

[![Watch the video](https://img.youtube.com/vi/k93ksGNNwZQ/default.jpg)](https://youtu.be/k93ksGNNwZQ)

### Details
Arduino is responsible for passing the keyboard input into the ESP-01 module (ESP8266 chip). After receiving an alphanumerical character via the serial connection, ESP passes a request to my webserver, which in turn calls the Tuya API based on the code. Arduino flashes a LED depending on the result (green - OK, yellow - website error, red - network error).

A few reasons behind this set-up:  
- Arduino UNO and ESP-01 were the only suitable devices I've had on hand;  
- I've ran into pin count limitations that prevented me from utilizing only the ESP-01;  
- I don't call the API directly from ESP, but rather store the light presets on my server in order to prevent unnecessary firmware flashes.  

### License
The project is licensed under the Apache License, Version 2.0.