/**
 * These functions are used to exchange neural network weights over the network
 * via JSON format, typically using WiFiClient on ESP32.
 */

#ifndef JSON_UTILITY_H
#define JSON_UTILITY_H    

#include "WString.h"
#include <WiFiClient.h> 

/**
 * @brief Sends an array of float weights in JSON format over a WiFiClient connection.
 *
 * The function serializes the weights array into a JSON string and sends it over
 * the provided TCP connection. Typically used for gossip-based model exchange.
 *
 * @param weights Array of float values representing model weights.
 * @param weight_number Number of weights in the array.
 * @param conn Reference to an active WiFiClient connection.
 */
void sendJson(float weights[], uint16_t weight_number, WiFiClient &conn);

/**
 * @brief Deserializes a JSON string into an array of floats.
 *
 * Parses a JSON-formatted string containing model weights and fills
 * the provided FlatWeights array with the extracted float values.
 *
 * @param weight_number Expected number of weights to extract.
 * @param FlatWeights Output array where the weights will be stored.
 * @param jsonString Input JSON string containing the weights.
 * @return String containing weights updated.
 */
String deserializeJsonToFloat(uint16_t weight_number, float FlatWeights[], String jsonString);

#endif // JSON_UTILITY_H
