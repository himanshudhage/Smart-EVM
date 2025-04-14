// Include the LiquidCrystal library for interfacing with the LCD
#include <LiquidCrystal.h>
// Initialize the LCD object with the pins connected to RS, E, D4, D5, D6, D7
LiquidCrystal lcd(4, 5, 6, 7, 10, 11);

// Include SoftwareSerial for serial communication with fingerprint module
#include <SoftwareSerial.h>
// Define software serial on pins 2 (RX) and 3 (TX)
SoftwareSerial mySerial(2, 3);

// Include Adafruit Fingerprint Sensor Library
#include "Adafruit_Fingerprint.h"
// Create fingerprint sensor object using the software serial
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// Define the buzzer pin
#define buzzer 13

// Boolean array to track which IDs have already voted (0-127)
bool hasVoted[128] = {false};

void setup() {
  // Start serial communication for debugging (Serial Monitor)
  Serial.begin(9600);
  
  // Start fingerprint sensor communication
  finger.begin(57600);

  // Set the buzzer pin as output
  pinMode(buzzer, OUTPUT);
  
  // Initialize the LCD with 16 columns and 2 rows
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Checking Module");

  // Check if fingerprint sensor is connected and responsive
  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor found!");
    lcd.clear();
    lcd.print("Module Connected");

    // Check all IDs (0 to 127) to see which ones are already stored in memory
    bool anyFingerprintFound = false;
    for (int id = 0; id <= 127; id++) {
      if (finger.loadModel(id) == FINGERPRINT_OK) {
        anyFingerprintFound = true;
        Serial.print("ID ");
        Serial.print(id);
        Serial.println(" exists.");
      }
    }

    // If no fingerprint is found in memory, show message on LCD
    if (!anyFingerprintFound) {
      Serial.println("No fingerprints found in storage.");
      lcd.setCursor(0, 1);
      lcd.print("No fingerprints");
    }

  } else {
    // If fingerprint sensor is not connected properly
    Serial.println("Fingerprint sensor not found :(");
    lcd.clear();
    lcd.print("Module not Found");
    lcd.setCursor(0, 1);
    lcd.print("Check Connections");
    while (1); // Infinite loop to halt further execution
  }

  delay(2000); // Delay to show the message
  lcd.clear(); // Clear LCD before going to main loop
}

void loop() {
  // Display prompt to place finger
  lcd.setCursor(0, 0);
  lcd.print("Place Finger");
  lcd.setCursor(0, 1);
  lcd.print("[ ]");

  // Check fingerprint and get result
  int result = checkFingerprint();
  
  if (result > 0) {
    // Fingerprint matched but user already voted
    lcd.clear();
    lcd.print("Already Voted");
    delay(3000);
  } else if (result == -1) {
    // No match or unregistered fingerprint
    lcd.clear();
  }

  lcd.clear(); // Clear LCD before restarting loop
}

// Function to buzz for short duration
void soundBuzzer() {
  digitalWrite(buzzer, HIGH); // Turn on buzzer
  delay(200); 
  digitalWrite(buzzer, LOW);  // Turn off buzzer
}

// Function to capture, process, and verify fingerprint
int checkFingerprint() {
  int result = -1; // Default: no match

  // Step 1: Capture fingerprint image
  if (finger.getImage() != FINGERPRINT_OK) return -1;

  // Step 2: Convert image to template
  if (finger.image2Tz() != FINGERPRINT_OK) return -1;

  // Step 3: Search the template in the stored database
  result = finger.fingerSearch();

  if (result == FINGERPRINT_OK) {
    // Match found
    int id = finger.fingerID;

    if (hasVoted[id]) {
      // Already voted, so reject
      lcd.clear();
      lcd.print("Already Voted");
      delay(3000);
      return id;
    }

    Serial.println("Fingerprint found in database.");
    soundBuzzer(); // Give feedback with buzzer

    lcd.clear();
    lcd.print("Welcome, User ");
    lcd.print(id); // Display ID of user
    delay(3000);

    hasVoted[id] = true; // Mark as voted
    return id;
  } else {
    // No match found in fingerprint database
    Serial.println("Fingerprint not found in database.");
    lcd.clear();
    lcd.print("Fake ID"); // Display warning
    delay(3000);
    return -1;
  }

  return -1; // Fallback
}
