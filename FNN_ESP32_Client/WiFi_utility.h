/**
 * This module handles Wi-Fi setup, debugging, and the communication of model weights 
 * (e.g., for gossip learning) between ESP32 devices over the network.
 */

#ifndef WIFI_UTILITY_H
#define WIFI_UTILITY_H

#include <Arduino.h>        
#include <WiFi.h>          
#include <ArduinoJson.h> 

//----- Wi-Fi configuration -----

/**
 * @brief SSID of the Wi-Fi network to connect to.
 */
extern const char *ssid;

/**
 * @brief Password for the Wi-Fi network.
 */
extern const char *password;

/**
 * @brief Port number used for TCP communication.
 */
extern const uint16_t port;

/**
 * @brief IP address of the target server or peer device.
 */
extern const char *server_ip;

/**
 * @brief Attempts to connect to the configured Wi-Fi network.
 * 
 * @param timeout_ms Maximum time to wait for connection (in milliseconds).
 * @return true if the connection was successful, false otherwise.
 */
bool connectToWiFi(uint32_t timeout_ms);

/**
 * @brief Prints debug information based on the current Wi-Fi state.
 * 
 * @param state Current state of the Wi-Fi connection.
 */
void debugWiFiConnection(uint8_t state);

/**
 * @brief Sets up the device as a Wi-Fi client.
 * 
 * This function prepares the ESP32 for TCP communication with a peer.
 * 
 * @return true if the client setup was successful, false otherwise.
 */
bool setup_WiFi_client();

/**
 * @brief Synchronizes model weights with a peer.
 * 
 * Sends the local weights over Wi-Fi and waits for a response containing 
 * updated weights (used in gossip learning scenarios).
 * 
 * @param weight_number Number of weights to send.
 * @param FlatWeights Array of weights to transmit and update.
 * @return A JSON-formatted string with updated weights.
 */
String syncWeights_client(uint16_t weight_number, float FlatWeights[]);

#endif //WIFI_UTILITY_H
