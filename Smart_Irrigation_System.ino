// Include necessary libraries
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pin and definition settings
#define DHTPIN 27      // Pin connected to the DHT22 sensor
#define DHTTYPE DHT22  // Define the type of DHT sensor
#define SOIL_SENSOR 33 // Pin for soil moisture sensor
#define RELAY 4        // Pin for relay

// Object initialization
DHT dht(DHTPIN, DHTTYPE);                  // Initialize DHT22 sensor
LiquidCrystal_I2C lcd(0x27, 16, 2);       // LCD configuration (address 0x27)

// Global variables
int soilMoisture = 0;    // Soil moisture value
float temp = 0.0;        // Ambient temperature
float humidity = 0.0;    // Ambient humidity

void setup() {
  // Start serial communication and configure pins
  Serial.begin(115200);
  dht.begin();
  lcd.begin();
  lcd.backlight();

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);  // Ensure relay is off initially

  // Display startup message on LCD
  lcd.setCursor(0, 0);
  lcd.print("System Started");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read data from the DHT22
  temp = dht.readTemperature();    // Read temperature
  humidity = dht.readHumidity();   // Read humidity

  // Check if DHT readings are valid
  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Error reading DHT sensor!");
    lcd.setCursor(0, 0);
    lcd.print("DHT Error!");
    delay(2000);
    return;
  }

  // Read soil moisture
  int rawValue = analogRead(SOIL_SENSOR);
  soilMoisture = map(rawValue, 0, 4095, 0, 100);
  soilMoisture = (soilMoisture - 100) * -1; // Invert value so 100 is wet soil

  // Display values on serial monitor
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("C, Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.println("%");

  // Display values on LCD screen
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print("C ");
  lcd.setCursor(0, 1);
  lcd.print("Soil: ");
  lcd.print(soilMoisture);
  lcd.print("%");

  // Control logic for the pump
  if (soilMoisture < 30 && temp < 30) {
    digitalWrite(RELAY, LOW); // Turn on pump
    Serial.println("Pump ON");
    lcd.setCursor(12, 1);
    lcd.print("ON ");
  } else {
    digitalWrite(RELAY, HIGH); // Turn off pump
    Serial.println("Pump OFF");
    lcd.setCursor(12, 1);
    lcd.print("OFF");
  }

  // Wait before next reading
  delay(2000);
}
