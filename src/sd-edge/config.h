#ifndef __CONFIG__
#define __CONFIG__

#define AV_PIN 2 // Available status led pin.
#define NAV_PIN 4 // Not available status led pin.

#define POT_PIN A0 // Potentiometer pin.

#define BAUD_RATE 9600 // Serial port baud rate.

#define SSID "" // WiFi name.
#define PWD "" // WiFi password.

#define PORT 3000 // Server port.

#define W_MAX 100 // Wmax value.

void connectWifi();
void sendData();
void getData();
void switchLed();

#endif