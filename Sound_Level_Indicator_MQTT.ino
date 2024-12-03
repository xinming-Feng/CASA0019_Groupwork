#include <Adafruit_NeoPixel.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiUdp.h>
#include "arduino_secrets.h"

// WiFi and MQTT configuration
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqtt_username = SECRET_MQTTUSER;
const char* mqtt_password = SECRET_MQTTPASS;
const char* mqtt_server = "mqtt.cetools.org";
const int mqtt_port = 1884;
const char* mqtt_topic = "student/ucfnadu/sound";

// LED strip configuration
#define LED_PIN D6
#define NUM_LEDS 144
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Sound sensor configuration
#define SOUND_PIN A0
int soundLevel = 0;
int numLedsToLight = 0;

// WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting setup...");

  strip.begin();        // Initialize LED strip
  strip.show();         // Turn off all LEDs initially
  Serial.println("LED strip initialized.");

  pinMode(SOUND_PIN, INPUT); // Set the sound level sensor pin as input
  Serial.println("Sound sensor pin configured.");

  // Connect to WiFi
  Serial.println("Attempting WiFi connection...");
  setupWifi();

  // Setup MQTT
  client.setServer(mqtt_server, mqtt_port);
  Serial.println("MQTT client configured.");
  
  client.setCallback(mqttCallback); // Callback for incoming MQTT messages

  Serial.println("Setup complete!");
}

void loop() {
  
  Serial.println("Starting loop iteration...");

  // Read sound level
  soundLevel = analogRead(SOUND_PIN);
  Serial.print("Raw sound level: ");
  Serial.println(soundLevel);

  // Map sound level to the number of LEDs
  numLedsToLight = map(soundLevel, 0, 1023, 0, NUM_LEDS);
  Serial.print("Number of LEDs to light up: ");
  Serial.println(numLedsToLight);

  // Update LED colors based on the sound level
  updateLEDColors(numLedsToLight);

  // Ensure WiFi and MQTT connections
  checkConnections();

  // Publish sound data to MQTT
  sendSoundDataToMQTT(soundLevel, numLedsToLight);

  // Debug statement for loop completion
  Serial.println("Loop iteration complete.");
  delay(100); // Delay to control update frequency
}

void setupWifi() {
  WiFi.mode(WIFI_STA); // Explicitly set station mode
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    delay(500);
  }
  
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    String clientId = "SoundLevelClient";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("MQTT connected!");
      client.subscribe(mqtt_topic); // Ensure subscription is restored
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.print(client.state());
      Serial.println(". Retrying in 2 seconds...");
      delay(2000);
    }
  }
}

void checkConnections() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected. Reconnecting...");
    setupWifi();
  }
  if (!client.connected()) {
    Serial.println("MQTT disconnected. Reconnecting...");
    reconnectMQTT();
  }
  client.loop(); // Maintain MQTT connection
}

void sendSoundDataToMQTT(int soundLevel, int numLeds) {
  char mqtt_message[100];
  snprintf(mqtt_message, sizeof(mqtt_message), "{\"soundLevel\": %d, \"numLedsLit\": %d}", soundLevel, numLeds);

  if (client.publish(mqtt_topic, mqtt_message)) {
    Serial.println("MQTT message published successfully.");
  } else {
    Serial.println("Failed to publish MQTT message.");
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);
  
  Serial.print("Message: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void updateLEDColors(int numLeds) {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < numLeds) {
      strip.setPixelColor(i, getLEDColor(soundLevel)); // Set color based on sound level
    } else {
      strip.setPixelColor(i, 0); // Turn off the LED
    }
  }
  strip.show(); // Update the strip with new colors
}

uint32_t getLEDColor(int soundLevel) {
  int dbLevel = map(soundLevel, 0, 1023, 30, 130);
  if (dbLevel <= 50) {
    return strip.Color(0, 255, 0); // Green
  } else if (dbLevel <= 70) {
    return strip.Color(255, 255, 0); // Yellow
  } else if (dbLevel <= 90) {
    return strip.Color(255, 165, 0); // Orange
  } else if (dbLevel <= 110) {
    return strip.Color(255, 0, 0); // Red
  } else {
    return strip.Color(255, 0, 255); // Magenta
  }
}
