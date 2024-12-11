#include <Adafruit_NeoPixel.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <TFT_eSPI.h> // TFT_eSPI library for SPI displays
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
#define LED_PIN D1
#define NUM_LEDS 284
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Sound sensor configuration
#define SOUND_PIN A0
int soundLevel = 0;
int numLedsToLight = 0;

TFT_eSPI tft = TFT_eSPI(); // Create an instance of the display

// WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

// Buffer to store amplitude data
#define BUFFER_SIZE 1
int amplitudeBuffer[BUFFER_SIZE] = {0};
int bufferIndex = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting setup...");

  // Initialize TFT display
  tft.init();
  tft.setRotation(1); // Set the display orientation
  tft.fillScreen(TFT_BLACK); // Clear the screen
  Serial.println("TFT display initialized.");

  // Initialize LED strip
  strip.begin();
  strip.show();
  Serial.println("LED strip initialized.");

  // Configure sound sensor pin
  pinMode(SOUND_PIN, INPUT);
  Serial.println("Sound sensor pin configured.");

  // Connect to WiFi
  Serial.println("Attempting WiFi connection...");
  setupWifi();

  // Setup MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(mqttCallback); // Callback for incoming MQTT messages
  Serial.println("MQTT client configured.");
  
  Serial.println("Setup complete!");
}

void loop() {
  Serial.println("Starting loop iteration...");

  // Read sound level and store in buffer
  soundLevel = analogRead(SOUND_PIN);
  amplitudeBuffer[bufferIndex] = soundLevel;
  bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;

  // Display the time-domain waveform
  displaySoundWave();

  // Map sound level to the number of LEDs
  numLedsToLight = map(soundLevel, 0, 800, 0, NUM_LEDS);
  updateLEDColors(numLedsToLight);

  // Ensure WiFi and MQTT connections
  checkConnections();

  // Publish sound data to MQTT
  sendSoundDataToMQTT(soundLevel, numLedsToLight);

  delay(50); // Adjust delay for smooth updates
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
  strip.show();
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

void displaySoundWave() {
  static int lastX = 0;
  static int lastY = 0;

  // Graph dimensions
  const int graphX = 0;
  const int graphY = 0;
  const int graphWidth = 480;
  const int graphHeight = 320;

  // Setup starting point for plotting
  if (lastX == 0) {
    lastY = graphY + graphHeight - map(amplitudeBuffer[0], 0, 1023, 0, graphHeight);
    tft.drawPixel(lastX + graphX, lastY, TFT_GREEN);  // Start point
  }

  // Increment position
  int x1 = lastX;
  int y1 = lastY;
  int x2 = x1 + 1;  // Move to next x position
  if (x2 >= graphWidth) {
    // Clear the graph and reset if we've hit the end
    tft.fillRect(graphX, graphY, graphWidth, graphHeight, TFT_BLACK);
    x1 = 0;
    x2 = 1;
  }

  // Compute the new y position
  int y2 = graphY + graphHeight - map(amplitudeBuffer[x2 % BUFFER_SIZE], 0, 1023, 0, graphHeight);

  // Clear only the old point and draw new point
  tft.fillRect(lastX + graphX, lastY, 1, 1, TFT_BLACK);  // Clear old point
  tft.drawLine(x1 + graphX, y1, x2 + graphX, y2, TFT_GREEN); // Draw the new line

  // Update last positions
  lastX = x2;
  lastY = y2;
}


