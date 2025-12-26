#include <Arduino.h>
#include <DHT.h>
#include "inference.h"

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    dht.begin();
    setupModel();
    Serial.println("Model loaded. Starting classification...");
}

void loop() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read DHT!");
        delay(2000);
        return;
    }

    Serial.print("Temperature: "); Serial.print(temperature);
    Serial.print(" °C | Humidity: "); Serial.print(humidity); Serial.println(" %");

    const char* predicted_env = runInference(temperature, humidity);
    Serial.print("Predicted environment: "); Serial.println(predicted_env);
    Serial.println("--------------------------");
    delay(3000);
}
