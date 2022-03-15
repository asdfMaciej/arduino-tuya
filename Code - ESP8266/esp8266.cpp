// Copyright 2022 Maciej Kaszkowiak (maciej@kaszkowiak.org)
// Apache License 2.0

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

ESP8266WiFiMulti WiFiMulti;

// The received character will be appended to the end of urlPrefix
char inputChar;
String urlPrefix = "https://yourwebsite.com/?secretparam=123&commandcode=";

// You might notice that the code outputs RGY on the serial port
//  - the characters stand for Red, Green and Yellow

void connect(String urlString) {
  char url[70];
  urlString.toCharArray(url, sizeof(url));

  // Flash red led on network error
  if ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.print("R");
    return;
  }

  // [!] Establishing an insecure connection, prone to MITM
  // An alternative is to embed server's fingerprint into the code 
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  // Send the GET request
  // Green on success, Yellow on server failure, Red on network failure
  if (https.begin(*client, url)) {
    int httpCode = https.GET();

    // httpCode might be negative on error
    if (httpCode > 0 && httpCode < 300) {
      Serial.printf("G");
    } else {
      Serial.printf("Y");
    }

    https.end();
  } else {
    Serial.printf("R");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.print("R");

  // Some extra delay to ensure set-up
  delay(5000);
  Serial.print("RYG");

  // Add as many AP points as you deem necessary - note: no 5GHz support
  // The order is equivalent to the priority during connection
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("MAIN_AP", "password1");
  WiFiMulti.addAP("SECONDARY_AP", "password2");
}

void loop() {
  // Connect to the given URL upon reading an uppercase letter/digit
  if (Serial.available() > 0) {
    inputChar = Serial.read();
    if (!(isUpperCase(inputChar) || isDigit(inputChar))) {
      // Output ? on err input
      Serial.println("?"); 
      return;
    }

    connect(urlPrefix + inputChar);
  }
}
