#include <HardwareSerial.h>
#include <TinyGPS++.h>

#define RX_PIN 12  // ESP32-S3 RX (EC200U TX)
#define TX_PIN 13  // ESP32-S3 TX (EC200U RX)
#define GNSS_BAUD 115200  // EC200U default baud rate

HardwareSerial GNSSSerial(1);  // Use UART1
TinyGPSPlus gps;

void sendATCommand(String cmd) {
    GNSSSerial.println(cmd);
    delay(500);  // Wait for module response
}

void setup() {
    Serial.begin(115200);  // Monitor output
    GNSSSerial.begin(GNSS_BAUD, SERIAL_8N1, RX_PIN, TX_PIN);

    Serial.println("Initializing EC200U GNSS...");

    sendATCommand("AT");  // Test AT command
    sendATCommand("AT+QGPSCFG=\"outport\",\"uart1\"");  // Set output to UART1
    sendATCommand("AT+QGPS=1");  // Turn on GNSS
}

void loop() {
    while (GNSSSerial.available()) {
        char c = GNSSSerial.read();
        Serial.write(c);  // Print raw NMEA output

        if (gps.encode(c)) {
            if (gps.location.isValid()) {
                float latitude = gps.location.lat();
                float longitude = gps.location.lng();

                Serial.print("Latitude: ");
                Serial.println(latitude, 6);
                Serial.print("Longitude: ");
                Serial.println(longitude, 6);

                // Generate Google Maps link
                Serial.print("Google Maps Link: ");
                Serial.print("https://www.google.com/maps/place/");
                Serial.print(latitude, 6);
                Serial.print(",");
                Serial.println(longitude, 6);
                
                delay(5000);  // Wait before next update
            } else {
                Serial.println("Waiting for GPS fix...");
            }
        }
    }
}
