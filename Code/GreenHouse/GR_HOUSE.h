# ifndef GR_HOUSE_H
# define GR_HOUSE_H

/*******Includin' needed libraries*********/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>
/*****************************************/

/******************Definin' Pins******************/

#define WATER_PUMP_PIN 3
#define COOLER_PIN 5
#define HEATER_PIN 4
#define MOISTURE_SENSOR_PIN A0
#define DHT11_PIN A1
#define TEMPERATURE_POT_PIN A2
#define HUMIDITY_POT_PIN A3
#define LCD_COLUMNS 16
#define LCD_ROWS 2

/**************************************************/

/***************Definin' Variables*****************/

int temperatureInterval;
int humidityInterval;
int soilMoistureThreshold = 500;
int waterPumpOnTime = 1000;
unsigned long previousWateringTime = 0;
int temperatureSetpoint;
int temperatureHysteresis = 2;

/**************************************************/

/**********************Creating instances**************************/

LiquidCrystal_I2C lcd(0x27, LCD_COLUMNS, LCD_ROWS);
/*to know the address of your i2c devices
  just use "I2c_scan" sketch example from the Libray "Wire" :) */
dht DHT;

/******************************************************************/

# endif
