/**
 * This module sets up the ESP32 in server mode, receives weight data from clients,
 * and responds with updated weights using JSON over TCP.
 */

#ifndef WIFI_UTILITY_H
#define WIFI_UTILITY_H

#include <Arduino.h>        
#include <WiFi.h>           
#include <ArduinoJson.h>  

//----- Wi-Fi Configuration -----

/**
 * @brief SSID of the Wi-Fi network.
 */
extern const char *ssid;

/**
 * @brief Password for the Wi-Fi network.
 */
extern const char *password;

/**
 * @brief Port used for TCP server communication.
 */
extern const uint16_t port;

/**
 * @brief IP address of the current ESP32 device (if needed externally).
 */
extern const char *server_ip;

//----- Utility Functions -----

/**
 * @brief Prints Wi-Fi connection state for debugging purposes.
 * 
 * @param state Wi-Fi connection status code (from WiFi.status()).
 */
void debugWiFiConnection(uint8_t state);

/**
 * @brief Connects the ESP32 to a Wi-Fi network.
 * 
 * @param timeout_ms Timeout in milliseconds to wait for successful connection.
 * @return true if connected successfully, false otherwise.
 */
bool connectToWiFi(uint32_t timeout_ms);

/**
 * @brief Sets up the ESP32 as a TCP server.
 * 
 * This function initializes the Wi-Fi server and waits for incoming client connections.
 * @return true if the server setup was successful.
 */
bool setup_WiFi_server();

/**
 * @brief Handles incoming model weights from a client and sends updated weights back.
 * 
 * Used in gossip learning: this function waits for a connection, receives weights
 * via JSON, optionally updates or merges them, and sends the response.
 * 
 * @param weight_number Number of weights expected.
 * @param FlatWeights Array containing local model weights, which may be updated based on received values.
 * @return A string containing weights in JSON.
 */
String syncWeights_server(uint16_t weight_number, float FlatWeights[]);

#endif // WIFI_UTILITY_H
