#include <LiquidCrystal.h> // Standard LCD library, not I2C
LiquidCrystal lcd(4, 5, 6, 7, 10, 11); // LCD pins: RS, E, D4, D5, D6, D7

#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX for fingerprint sensor

#include "Adafruit_Fingerprint.h"
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

#define buzzer 13 // Buzzer pin

// Array to keep track of IDs that have already voted (128 elements for IDs 0-127)
bool hasVoted[128] = {false};

void setup() {
  Serial.begin(9600);
  finger.begin(57600);

  pinMode(buzzer, OUTPUT); // Set buzzer as output
  
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.setCursor(0, 0);
  lcd.print("Checking Module");

  // Verify the fingerprint sensor connection
  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor found!");
    lcd.clear();
    lcd.print("Module Connected");

    // Check for fingerprints from ID 0 to 127
    bool anyFingerprintFound = false;
    for (int id = 0; id <= 127; id++) {
      if (finger.loadModel(id) == FINGERPRINT_OK) {
        anyFingerprintFound = true;
        Serial.print("ID ");
        Serial.print(id);
        Serial.println(" exists.");
      }
    }

    // Display if no fingerprints are found
    if (!anyFingerprintFound) {
      Serial.println("No fingerprints found in storage.");
      lcd.setCursor(0, 1);
      lcd.print("No fingerprints");
    }
    
  } else {
    Serial.println("Fingerprint sensor not found :(");
    lcd.clear();
    lcd.print("Module not Found");
    lcd.setCursor(0, 1);
    lcd.print("Check Connections");
    while (1); // Stop here if no sensor is found
  }
  
  delay(2000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Place Finger");
  lcd.setCursor(0, 1);
  lcd.print("[ ]");

  int result = checkFingerprint();
  
  if (result > 0) { // If fingerprint found in database
    lcd.clear();
    lcd.print("Already Voted");
    delay(3000); // Display message for 3 seconds
  } else if (result == -1) { // If fingerprint is new or not found
    lcd.clear();
  }
  
  lcd.clear();
}

// Function to sound the buzzer quickly
void soundBuzzer() {
  digitalWrite(buzzer, HIGH); // Sound the buzzer
  delay(200); 
  digitalWrite(buzzer, LOW);
}

// Function to check if a fingerprint matches an existing one in the database
int checkFingerprint() {
  int result = -1; // Assume no match by default

  if (finger.getImage() != FINGERPRINT_OK) return -1;
  if (finger.image2Tz() != FINGERPRINT_OK) return -1;

  result = finger.fingerSearch();

  if (result == FINGERPRINT_OK) {
    int id = finger.fingerID;

    if (hasVoted[id]) {
      lcd.clear();
      lcd.print("Already Voted");
      delay(3000);
      return id; // Return the ID, as they have already voted
    }

    Serial.println("Fingerprint found in database.");
    soundBuzzer(); // Sound buzzer as soon as a match is found
    
    lcd.clear();
    lcd.print("Welcome, User ");
    lcd.print(id);
    delay(3000);
    
    hasVoted[id] = true; // Mark this ID as having voted
    return id;
  } else {
    Serial.println("Fingerprint not found in database.");
    lcd.clear();
    lcd.print("Fake ID");
    delay(3000);
    return -1; // No match found
  }
  
  return -1; // No match if outside 0-127
}