#include <Wire.h>
#include <Adafruit_Sensor.h>  // https://github.com/adafruit/Adafruit_Sensor
// sensor data from AHT10 module
#include <Adafruit_AHTX0.h> // https://github.com/adafruit/Adafruit_AHTX0
Adafruit_AHTX0 aht10;
sensors_event_t aht10Temp, aht10Hum;

float temperature = -99;
float humidity = -99;

// ----------------------------------------------------------------
// vars for "delay" without blocking the loop
const unsigned long period2s = 2000;    //the value is a number of milliseconds, ie 2 second
const unsigned long period3s = 3000;    //the value is a number of milliseconds, ie 3 seconds
const unsigned long period10s = 10000;  //the value is a number of milliseconds, ie 10 seconds
const unsigned long period30s = 30000;  //the value is a number of milliseconds, ie 30 seconds
unsigned long currentMillis;
unsigned long previousMillisDisplay = 0;

void setup() 
{
  Serial.begin(115200);
  Wire.begin(10,9);
  Serial.println(F("Environment Sensor AHT10"));
  // ----------------------------------------------------------------
  // setup the sensor
  // AHT10 Temp + Humidity sensor
  if (! aht10.begin()) {
    Serial.println(F("Could not find AHT? Check wiring"));
    while (1) delay(10);
  }
  Serial.println(F("AHT10 or AHT20 found"));
}

void loop() 
{
  currentMillis = millis();
  if (currentMillis - previousMillisDisplay > period2s) 
  {
    getAht10Values();
    printValues();
   
    previousMillisDisplay = currentMillis;
  }
}

void getAht10Values() 
{
  aht10.getEvent(&aht10Hum, &aht10Temp);// populate temp and humidity objects with fresh data
  temperature = aht10Temp.temperature;
  humidity = aht10Hum.relative_humidity;
}

void printValues() 
{
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.println();
}
