#include <OneWire.h>
#include <DallasTemperature.h>

// Change to any safe GPIO pin on your ESP32-S3
#define ONE_WIRE_BUS 7  // For example, GPIO5

// Setup a oneWire instance
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature sensor library
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();  // Initialize the DS18B20 sensor
  Serial.println("DS18B20 Temperature Sensor Test - ESP32-S3");
}

void loop() {
  sensors.requestTemperatures();  // Request temperature from sensor

  float temp = sensors.getTempCByIndex(0);  // Read temperature

  if (temp == -127.0) {
    Serial.println("Failed to read from DS18B20 sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");
  }

  delay(2000);
}
