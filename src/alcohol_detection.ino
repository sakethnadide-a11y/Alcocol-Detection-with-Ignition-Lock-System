
#include <Arduino.h>
#include <U8g2lib.h>
#include <SoftwareSerial.h>
#include <DFRobot_SIM808.h>

// Pin Definitions
const int ENA = 5;          // PWM pin for motor speed control
const int IN1 = 7;          // Motor direction pin
const int IN2 = 8;          // Motor direction pin
const int buzzer = 13;      // Buzzer pin
const int sensorPin = A0;   // Alcohol sensor pin

// Alcohol Detection Threshold
const int thresholdValue = 500;

// Initialize U8g2 for 4-pin I2C LCD display
U8G2_SSD1306_128X64_NONAME_2_HW_I2C u8g2(
    U8G2_R0,
    U8X8_PIN_NONE
);

// SIM808 Communication (RX = 10, TX = 11)
SoftwareSerial sim808Serial(10, 11);
DFRobot_SIM808 sim808(&sim808Serial);

// Variables
int motorSpeed = 255;
bool alcoholDetected = false;


// Function Declarations
void displayValues(int alcoholValue, int threshold, int speed);
void sendAlertSMS(const char* phoneNumber, const char* message);


void setup() {

    // Configure pin modes
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(sensorPin, INPUT);

    // Initialize motor direction
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    // Initialize LCD display
    u8g2.begin();

    // Start motor at maximum speed
    analogWrite(ENA, motorSpeed);

    // Initialize SIM808 and Serial communication
    sim808Serial.begin(9600);
    Serial.begin(9600);

    if (sim808.init()) {
        Serial.println("SIM808 initialized successfully!");
    }
    else {
        Serial.println("Failed to initialize SIM808!");
    }
}


void loop() {

    // Read alcohol sensor value
    int alcoholValue = analogRead(sensorPin);

    // Display current sensor readings
    displayValues(alcoholValue, thresholdValue, motorSpeed);

    // Check whether alcohol exceeds the threshold
    if (alcoholValue >= thresholdValue && !alcoholDetected) {

        alcoholDetected = true;

        // Activate buzzer for 10 seconds
        tone(buzzer, 1000);
        delay(10000);
        noTone(buzzer);

        // Gradually reduce motor speed from 255 to 0
        for (motorSpeed = 255; motorSpeed >= 0; motorSpeed--) {

            analogWrite(ENA, motorSpeed);

            // Update LCD display
            displayValues(alcoholValue, thresholdValue, motorSpeed);

            delay(39);
        }

        // Send SMS alert through SIM808
        // Replace placeholder locally if using SMS.
        sendAlertSMS(
            "+91XXXXXXXXXX",
            "Alcohol over limit detected!"
        );

        // Ensure motor is completely stopped
        analogWrite(ENA, 0);
        motorSpeed = 0;
    }

    // Refresh display every 500 milliseconds
    delay(500);
}


// Display Alcohol Value, Threshold and Motor Speed
void displayValues(int alcoholValue, int threshold, int speed) {

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tr);

    // Display alcohol sensor reading
    u8g2.setCursor(0, 7);
    u8g2.print("Alcohol Value: ");
    u8g2.print(alcoholValue);

    // Display threshold or motor speed
    u8g2.setCursor(0, 15);

    if (alcoholValue < threshold) {

        u8g2.print("Threshold: ");
        u8g2.print(threshold);

    }
    else {

        u8g2.print("Motor Speed: ");
        u8g2.print(speed);
    }

    // Update LCD
    u8g2.sendBuffer();
}


// Send SMS Alert Using SIM808 Module
void sendAlertSMS(const char* phoneNumber, const char* message) {

    // Set SMS mode to text
    sim808Serial.print("AT+CMGF=1\r");
    delay(1000);

    // Specify recipient phone number
    sim808Serial.print("AT+CMGS=\"");
    sim808Serial.print(phoneNumber);
    sim808Serial.print("\"\r");
    delay(1000);

    // Send SMS message
    sim808Serial.print(message);
    delay(1000);

    // Send Ctrl+Z to submit SMS
    sim808Serial.write(26);
    delay(5000);

    Serial.println("SMS send command completed!");
}
