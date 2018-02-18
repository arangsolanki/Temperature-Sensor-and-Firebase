#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11

// Set these to run example.
#define FIREBASE_HOST "........."
#define FIREBASE_AUTH "........."
#define WIFI_SSID "........."
#define WIFI_PASSWORD "........."

#define dht_dpin 0
DHT dht(dht_dpin, DHTTYPE); 

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  dht.begin();
  Serial.println("Humidity and temperature\n\n");
  delay(700);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    
}

int button = 0;
float light = 0.0;

void loop() {
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Firebase.setFloat("temperature", t);
  Firebase.setFloat("humidity", h);         
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t); 
  Serial.println("C  ");
  delay(1000);
}
