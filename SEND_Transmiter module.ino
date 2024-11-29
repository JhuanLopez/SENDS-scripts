#include <Adafruit_Fingerprint.h>
#include <WiFiManager.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Define pins for the hardware serial communication
#define RX_PIN 16  // GPIO pin for RX (receive)
#define TX_PIN 17  // GPIO pin for TX (transmit)

// Define button pins
#define BUTTON_REGISTER_PIN 22  // Pin for Register button
#define BUTTON_VERIFY_PIN 23    // Pin for Verify button

// Define LED pins
#define RECOGNIZED_LED_PIN 0  // Pin for Registered LED
#define INVALID_LED_PIN 4     // Pin for Invalid LED

// WiFi
const char* AP_SSID = "SENDS";  // WiFi SSID
const char* AP_PASS = "User@123";   // WiFi Password
bool isWiFiConnected;              // variable for checking if the Esp is connected to the wifi

// FirebaseDB
#define API_KEY "AIzaSyD5Ix0YzZ-k7pZMiJE-fAAivpyq0on0myA"
#define DATABASE_URL "https://sendclients-31a21-default-rtdb.asia-southeast1.firebasedatabase.app/"

FirebaseData fdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

// Instance of Fingerprint
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

// Instance of WiFiManager
void setup() {
  WiFiManager WiFi;

  // Initialize hardware Serial2 for fingerprint sensor communication
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);  // Baud rate 9600, RX and TX pins for fingerprint sensor

  // Set button pins as input
  pinMode(BUTTON_REGISTER_PIN, INPUT_PULLUP);  // Use internal pull-up resistor
  pinMode(BUTTON_VERIFY_PIN, INPUT_PULLUP);    // Use internal pull-up resistor

  // Set LED pins as output
  pinMode(RECOGNIZED_LED_PIN, OUTPUT);
  pinMode(INVALID_LED_PIN, OUTPUT);

  // Initially turn off both LEDs
  digitalWrite(RECOGNIZED_LED_PIN, LOW);
  digitalWrite(INVALID_LED_PIN, LOW);

  Serial.begin(115200);  // Debugging communication with the computer

  // WiFi Access Point
  isWiFiConnected = WiFi.autoConnect(AP_SSID, AP_PASS);
  if (!isWiFiConnected) {
    Serial.print("Failed To Connect");
    delay(3000);
    ESP.restart();
  } else {
    Serial.println("Connection Established");
    delay(3000);
  }

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Corrected sign-up check
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Signup OK");
    delay)(2000);
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  Serial.println("Fingerprint sensor setup...");
  if (finger.verifyPassword()) {
    Serial.println("DY50 Connected");
  } else {
    Serial.println("Error No Sensor Found");
    delay(5000);
    ESP.restart();
    while (1)
      ;  // Stay here if sensor is not detected
  }
}

void loop() {

}
