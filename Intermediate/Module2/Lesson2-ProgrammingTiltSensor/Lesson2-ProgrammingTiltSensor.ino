int ledPin = 13;  //variable for the LED Pin
int tilt = 2;     //variable for the Tilt Sensor Pin

int tiltStatus = 0;  //variable for the tiltsensor status - setting the status to 0 first

void setup() {
  pinMode(ledPin, OUTPUT);  // setting pin functionality of LED to Output
  pinMode(tilt, INPUT);     // setting pin functionality of Tilt Sensor to Input
}

void loop() {
  tiltStatus = digitalRead(tilt);

  if (tiltStatus == HIGH) { //if-else statement to make the LED light up when the condition is met - Tilt reading HIGH
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  delay(50);
}