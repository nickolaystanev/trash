#include <Servo.h>
Servo servoMain;

#define trigPin 13
#define echoPin 12
const int TOUCH_BUTTON_PIN = 2;
const int LED_PIN = 12;
const int pResistor = A0; // Photoresistor at Arduino analog pin A0
const int ledPinPresistor = 8;
int buttonState = 0;
int pResistorvalue;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(TOUCH_BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(ledPinPresistor, OUTPUT);
  pinMode(pResistor, INPUT);
  servoMain.attach(10);
}

void loop() {
  if (capacity() == true) {
    RotateReel(90);
  }
  else {
    Serial.println("asd");
    if (photoCheck() == true) {
      RotateReel(180);
    } else {
      RotateReel(0);
    }
  }
}


bool photoCheck()
{
  int value = analogRead(pResistor);
  Serial.println(value);
  if (value > 500) {
    digitalWrite(ledPinPresistor, HIGH);  //Turn led off
    return true;
  }
  digitalWrite(ledPinPresistor, LOW ); //Turn led on
  return false;
}

bool capacity()
{
  int state = digitalRead(TOUCH_BUTTON_PIN);
  // If a touch is detected, turn on the LED
  Serial.println(state);
  if (state == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    return true;
  }

  digitalWrite(LED_PIN, LOW);
  return false;
}

bool distance()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.println(distance);
  if (distance < 4) {
    return true;
  }
  return false;
}

void RotateReel(int degrees)
{
  servoMain.write(degrees);
  delay(5000);
  servoMain.write(90);
  delay(5000);
}


