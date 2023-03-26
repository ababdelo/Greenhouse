
#include "GR_HOUSE.h"

/*****************************Setup Function*******************************/
void setup() {
  pinMode(MOISTURE_SENSOR_PIN, INPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  pinMode(COOLER_PIN, OUTPUT);
  pinMode(HEATER_PIN, OUTPUT);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  //display initial message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Greenhouse");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring...");
  delay(2000);
}
/*************************************************************************/

/***************************Loop Function*********************************/
void loop() {
  // Read temperature from DHT11 sensor
  int temperature_val = DHT.temperature;

  // Read temperature interval from potentiometer
  temperatureInterval = map(analogRead(TEMPERATURE_POT_PIN), 0, 1023, 1, 10);

  // Check if temperature is above or below setpoint and adjust heating/cooling accordingly
  if (temperature_val > temperatureSetpoint + temperatureHysteresis) {
    digitalWrite(HEATER_PIN, LOW);
    digitalWrite(COOLER_PIN, HIGH);
  } else if (temperature_val < temperatureSetpoint - temperatureHysteresis) {
    digitalWrite(COOLER_PIN, LOW);
    digitalWrite(HEATER_PIN, HIGH);
  } else {
    digitalWrite(COOLER_PIN, LOW);
    digitalWrite(HEATER_PIN, LOW);
  }

  // Read humidity interval from potentiometer
  humidityInterval = map(analogRead(HUMIDITY_POT_PIN), 0, 1023, 1, 10);

  // Read soil moisture level and water the plants if necessary
  int soilMoisture = analogRead(MOISTURE_SENSOR_PIN);
  if (soilMoisture < soilMoistureThreshold && millis() - previousWateringTime > humidityInterval * 1000UL) {
    digitalWrite(WATER_PUMP_PIN, HIGH);
    delay(waterPumpOnTime);
    digitalWrite(WATER_PUMP_PIN, LOW);
    previousWateringTime = millis();
  }

  // Display temperature and humidity on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature_val);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humid: ");
  lcd.print(soilMoisture);
  lcd.print("C");

  // Wait for a moment before updating the display again
  delay(1000);
}
/************************************************************************/
