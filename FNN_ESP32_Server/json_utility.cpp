#include "HardwareSerial.h"
#include <ArduinoJson.h>
#include <WiFiClient.h>

void sendJson(float weights[], uint16_t weight_number, WiFiClient &conn) {
  const size_t capacity = JSON_ARRAY_SIZE(weight_number) + weight_number * 16 + 64;
  DynamicJsonDocument doc(capacity);
  JsonArray arr = doc.createNestedArray("floatArray");

  for (uint16_t i = 0; i < weight_number; ++i) {
    arr.add(weights[i]);
  }

  serializeJson(doc, conn);
  conn.println();
}

String deserializeJsonToFloat(uint16_t weight_number, float FlatWeights[], String jsonString) {

  const size_t capacity = JSON_ARRAY_SIZE(weight_number) + weight_number * 16 + 64;
  DynamicJsonDocument doc(capacity);

  DeserializationError error = deserializeJson(doc, jsonString);
  if (error) {
    Serial.print("Error deserialization: ");
    Serial.println(error.c_str());
    return "";
  }

  if (!doc.containsKey("floatArray")) {
    Serial.println("JSON missing 'floatArray'");
    return "";
  }

  JsonArray arr = doc["floatArray"];
  if (arr.size() != weight_number) {
    Serial.print("Mismatched weight count. Expected ");
    Serial.print(weight_number);
    Serial.print(", got ");
    Serial.println(arr.size());
    return "";
  }


  for (uint16_t i = 0; i < weight_number; i++) {
    float incoming_value = arr[i];
    FlatWeights[i] = (FlatWeights[i] + incoming_value) / 2.0f;
  }

  DynamicJsonDocument outDoc(capacity);
  JsonArray avgArr = outDoc.createNestedArray("floatArray");
  for (uint16_t i = 0; i < weight_number; i++) {
    avgArr.add(FlatWeights[i]);
  }

  String w;
  serializeJson(outDoc, w);
  return w;
}

 