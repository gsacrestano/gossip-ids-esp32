**Distributed Intrusion Detection System (IDS) for IoT devices (ESP32) based on Gossip Learning.** 
This project implements a decentralized Intrusion Detection System (IDS) for IoT environments, leveraging a Feedforward Neural Network (FNN) trained through Gossip Learning. The model is designed to run on ESP32 microcontrollers, enabling collaborative learning without centralized data collection.
Developed as part of my Bachelor's thesis and internship, this system demonstrates how federated learning techniques can be applied to resource-constrained IoT devices for network security purposes.

---

## Requirements

- ESP32 board  
- [AIfES library](https://github.com/embedded-machine-learning/aifes) for local neural network training  
- ArduinoJson library  
- WiFi library (built-in for ESP32)  
- Arduino IDE or PlatformIO  

---

## Project Structure

| File/Folder                 | Description                      |
|-----------------------------|----------------------------------|
| `FNN_ESP32_Client/`         | Code for ESP32 used as Client.   |
| `FNN_ESP32_Server`          | Code for ESP32 used as Server.   |
| `FNN_Evaluation_ESP32.ipynb`| Notebook for network evaluation. |

---

## How to Use on Your ESP32 Device

Follow these steps to deploy and run the IDS on your own ESP32 node:

1. **Setup your development environment**  
   Install Arduino IDE or PlatformIO and configure it for ESP32 development.

2. **Install required libraries**  
   - AIfES (neural network training)  
   - ArduinoJson (JSON handling)  
   - WiFi (usually pre-installed for ESP32)

3. **Configure Wi-Fi credentials**  
   Edit wifi_utility.h in each folder, or a separate config file, to set your SSID, password, server IP, and port.

4. **Load the dataset**  
   Use your own network traffic dataset formatted with 15 features per sample or use the provided example data.

5. **Build and upload the firmware**  
   Compile and flash the code onto your ESP32 device.

6. **Run the device**  
   The ESP32 will connect to Wi-Fi, train the local FNN, and start gossip communication with peers to sync weights.

7. **Monitor output**  
   Use serial monitor to observe training loss, inference results, and gossip sync logs.

---

## How Gossip Learning Works Here

- Each ESP32 node trains its local FNN on local data samples.  
- Periodically, nodes exchange their model weights over Wi-Fi using a simple TCP protocol with JSON serialization.  
- Received weights are merged to improve the model globally in a decentralized manner.  
- This approach enhances the IDS accuracy without needing centralized data aggregation.

---

## License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

---
