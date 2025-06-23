#include "pgmspace.h"
#include <cstring>
#include "HardwareSerial.h"
#include "WString.h"
#include "Arduino.h"
#include "JSON_utility.h"
#include "WiFi_utility.h"

const char *ssid = "ssid";
const char *password = "password";

const uint16_t port = 80;
const char *server_ip = "192.168.1.184";


WiFiServer server(port);
WiFiClient client;

void debugWiFiConnection(uint8_t state) {
  switch (state) {
  case WL_IDLE_STATUS:
    Serial.println("Idle");
    break;
  case WL_NO_SSID_AVAIL:
    Serial.println("SSID not available");
    break;
  case WL_SCAN_COMPLETED:
    Serial.println("Scan completed");
    break;
  case WL_CONNECT_FAILED:
    Serial.println("Connection failed");
    break;
  case WL_CONNECTION_LOST:
    Serial.println("Connection lost");
    break;
  case WL_DISCONNECTED:
    Serial.println("Disconnected");
    break;
  default:
    Serial.printf("Unknown status: %d\n", state);
    break;
  }
}
bool connectToWiFi(uint32_t timeout_ms = 20000) {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  uint32_t start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < timeout_ms) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi connected");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    return true;
  } else {
    Serial.println("\nWi-Fi connection failed");
    debugWiFiConnection(WiFi.status());
    return false;
  }
}
bool setup_WiFi_client() {
  IPAddress apIP(192, 168, 1, 185);
  WiFi.config(apIP);
  if (!connectToWiFi())
    return false;

  Serial.printf("Connecting to server at %s:%u...\n", server_ip, port);
  uint32_t start = millis();
  while (!client.connect(server_ip, port)) {
    if (millis() - start > 15000) {
      Serial.println("Server connection timeout!");
      return false;
    }
    delay(100);
  }

  Serial.println("Connected to server");
  return true;
}
String syncWeights_client(uint16_t weight_number, float FlatWeights[]) {
  Serial.println("Connecting to server...");

  if (!client.connect(server_ip, port)) {
    Serial.println("Connection failed");
    return "";
  }

  Serial.println("Connected");
  client.setTimeout(5000);
  sendJson(FlatWeights, weight_number, client);

  String response = "";
  uint32_t start = millis();
  while (millis() - start < 5000) {
    if (client.available()) {
      response = client.readStringUntil('\n');
      Serial.print("Server response: ");
      Serial.println(response);
      break;
    }
    delay(10);
  }

  if (response.isEmpty()) {
    Serial.println("No response (timeout)");
  }

  client.stop();
  return response;
}




