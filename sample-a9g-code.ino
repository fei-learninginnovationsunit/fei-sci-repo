#include <SoftwareSerial.h>

// Define the RX and TX pins for SoftwareSerial communication
const int A9G_RX = 2; // Connect A9G TX to Arduino digital pin 2
const int A9G_TX = 3; // Connect A9G RX to Arduino digital pin 3

SoftwareSerial A9GSerial(A9G_RX, A9G_TX);

void setup() {
  // Start communication with Arduino IDE Serial Monitor
  Serial.begin(9600);
  while (!Serial);

  // Start communication with A9G module
  A9GSerial.begin(115200);

  // Wait for the A9G module to initialize
  delay(1000);
  
  // Check network registration
  checkNetworkRegistration();

  // Get CCID information
  getCCID();

  // Get signal strength
  getSignalStrength();

  Serial.println("A9G SMS Sender Initialized");
}

void loop() {
  // Check if there is data available from the Arduino IDE Serial Monitor
  if (Serial.available()) {
    // Read the command from the Serial Monitor
    String command = Serial.readStringUntil('\n');

    // Check if the command is not empty
    if (command.length() > 0) {
      // Send SMS using the A9G module
      sendSMS("+1234567890", command); // Replace with the desired phone number

      // Print a message to the Arduino IDE Serial Monitor
      Serial.println("SMS Sent!");
    }
  }
}

// Function to check network registration
void checkNetworkRegistration() {
  A9GSerial.println("AT+CREG?");
  delay(1000);
  while (A9GSerial.available()) {
    Serial.write(A9GSerial.read());
  }
  Serial.println();
}

// Function to get CCID information
void getCCID() {
  A9GSerial.println("AT+CCID");
  delay(1000);
  while (A9GSerial.available()) {
    Serial.write(A9GSerial.read());
  }
  Serial.println();
}

// Function to get signal strength
void getSignalStrength() {
  A9GSerial.println("AT+CSQ");
  delay(1000);
  while (A9GSerial.available()) {
    Serial.write(A9GSerial.read());
  }
  Serial.println();
}

// Function to send an SMS using A9G module
void sendSMS(String phoneNumber, String message) {
  // Set SMS text mode
  A9GSerial.println("AT+CMGF=1");
  delay(1000);

  // Specify the phone number
  A9GSerial.print("AT+CMGS=\"");
  A9GSerial.print(phoneNumber);
  A9GSerial.println("\"");
  delay(1000);

  // Send the SMS message
  A9GSerial.print(message);
  delay(100);
  A9GSerial.write(26); // ASCII code for Ctrl+Z to send the SMS
  delay(1000);
}
