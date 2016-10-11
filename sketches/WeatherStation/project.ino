
#include <Wire.h>          // from standard libs
#include <LiquidCrystal.h> // from standard libs
#include "Sodaq_DS3231.h"  // from github.com/SodaqMoja/Sodaq_DS3231
#include "dht.h"           // github.com/RobTillaart/Arduino/tree/master/libraries/DHTlib

// Initialize LCD with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Initialize temp/ humidity sensor
dht DHT;
#define DHT11_PIN 7 // DHT sensor on PIN 7
#define GAS_PIN A0  // MQ135 sensor on PIN A0

char weekDay[][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
DateTime now = 0;


void setup() {
  Serial.begin(9600);  // Set baud rate
  Wire.begin();        // Start I2C
  rtc.begin();         // Start clock module
  pinMode(GAS_PIN, INPUT); // Set gas sensor pin
  lcd.begin(16, 2);    // Set LCD number of columns and rows
}


void printTime() {
  // Print on serial conn
  Serial.print(weekDay[now.dayOfWeek()]);
  Serial.print(", ");
  Serial.print(now.year(), DEC);
  Serial.print("-");
  Serial.print(now.month(), DEC);
  Serial.print("-");
  Serial.print(now.date(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  // Print on LCD screen
  lcd.print("T:");
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
}

void printTemp1() {
  // Print on serial conn
  Serial.print("Temperature (°C): ");
  Serial.println(DHT.temperature);
  // Print on LCD screen
  lcd.print("T1:");
  lcd.print((int)DHT.temperature);
}

void printTemp2() {
  rtc.convertTemperature();    // Convert current temperature into registers
  Serial.print("Clock temp: ");
  Serial.println(rtc.getTemperature()); // Read registers and display the temp
  // Print on LCD screen
  lcd.print(" T2:");
  lcd.print(rtc.getTemperature());
}

void printHumidity() {
  // Print on serial conn
  Serial.print("Humidity (%): ");
  Serial.println(DHT.humidity);
  // Print on LCD screen
  lcd.print(" H:");
  lcd.print((int)DHT.humidity);
  lcd.print("% ");
}

void printGas() {
  // Print on serial conn
  Serial.print("Gas: ");
  Serial.println(analogRead(GAS_PIN));
}


void loop() {
  Serial.println();
  now = rtc.now(); // Read current date-time
  int chk = DHT.read11(DHT11_PIN); // Read temp/ humidity

  lcd.setCursor(0, 0);
  printTime();
  printHumidity();

  lcd.setCursor(0, 1);
  printTemp1();
  printTemp2();

  delay(1000);
}
