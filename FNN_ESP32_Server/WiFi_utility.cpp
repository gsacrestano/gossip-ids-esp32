#include <Arduino.h>
#include <WiFi.h>
#include "WiFi_utility.h"
#include "JSON_UTILITY.h"

const char *ssid = "ssid";
const char *password = "password";

const uint16_t port = 80;
const char *server_ip = "192.168.1.184";

WiFiServer server(port);

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
  Serial.print("Connecting to Wi-Fi...");
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
bool setup_WiFi_server() {
  IPAddress apIP;
  apIP.fromString(server_ip);
  WiFi.config(apIP);

  if (connectToWiFi()) {
    server.begin();
    Serial.println("Server started");
    return true;
  }
  return false;
}
String syncWeights_server(uint16_t weight_number, float FlatWeights[]) {

  uint32_t start = millis();
  while (millis() - start < 10000) {
    WiFiClient incoming = server.available();

    if (incoming) {
      Serial.println("New client connected");
      incoming.setTimeout(2000);
      String message = incoming.readStringUntil('\n');

      if (message.length() > 0) {
        Serial.print("Client data: ");
        Serial.println(message);
        sendJson(FlatWeights, weight_number, incoming);
      } else {
        Serial.println("Client disconnected (empty)");
      }

      incoming.stop();
      return message;
    }
  }
  return "";
}