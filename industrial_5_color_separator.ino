#include <Servo.h>

// ---------------------------
// 5-Color Object Separator
// Arduino Uno + TCS3200
// ---------------------------

Servo gate1;
Servo gate2;
Servo gate3;
Servo gate4;
Servo gate5;

// TCS3200 sensor pins
const int S0 = 11;
const int S1 = 12;
const int S2 = A0;
const int S3 = A1;
const int sensorOut = 2;
const int sensorLED = 4;

// Servo pins
const int SERVO1_PIN = 3;
const int SERVO2_PIN = 5;
const int SERVO3_PIN = 6;
const int SERVO4_PIN = 9;
const int SERVO5_PIN = 10;

// Servo positions
const int GATE_OPEN = 90;
const int GATE_CLOSED = 15;
const int SORTING_DELAY = 600;

// Color thresholds (tune after calibration)
const int RED_LOW = 25;
const int RED_HIGH = 120;
const int GREEN_LOW = 20;
const int GREEN_HIGH = 105;
const int BLUE_LOW = 18;
const int BLUE_HIGH = 95;

String detectedColor = "UNKNOWN";

void setup() {
  Serial.begin(9600);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(sensorLED, OUTPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);   // Output frequency scaling = 20%
  digitalWrite(sensorLED, HIGH);

  gate1.attach(SERVO1_PIN);
  gate2.attach(SERVO2_PIN);
  gate3.attach(SERVO3_PIN);
  gate4.attach(SERVO4_PIN);
  gate5.attach(SERVO5_PIN);

  setAllGatesClosed();
  Serial.println("5-Color Separator Initialized");
  Serial.println("Place object under sensor");
}

void loop() {
  int red = readColor('R');
  int green = readColor('G');
  int blue = readColor('B');

  Serial.print("R:");
  Serial.print(red);
  Serial.print(" G:");
  Serial.print(green);
  Serial.print(" B:");
  Serial.println(blue);

  if (red > green && red > blue) {
    if (red >= RED_LOW && red <= RED_HIGH) {
      detectedColor = "RED";
      sortObject(1);
    }
  } else if (green > red && green > blue) {
    if (green >= GREEN_LOW && green <= GREEN_HIGH) {
      detectedColor = "GREEN";
      sortObject(2);
    }
  } else if (blue > red && blue > green) {
    if (blue >= BLUE_LOW && blue <= BLUE_HIGH) {
      detectedColor = "BLUE";
      sortObject(3);
    }
  } else if (red > 70 && green > 40 && blue < 80) {
    detectedColor = "YELLOW";
    sortObject(4);
  } else if (red > 120 && green > 120 && blue > 120) {
    detectedColor = "WHITE";
    sortObject(5);
  } else {
    detectedColor = "UNKNOWN";
    Serial.println("Color not matched. Adjust thresholds.");
  }

  Serial.print("Detected: ");
  Serial.println(detectedColor);
  delay(800);
}

int readColor(char color) {
  int value = 0;

  if (color == 'R') {
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
  } else if (color == 'G') {
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
  } else if (color == 'B') {
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
  }

  delay(20);
  value = pulseIn(sensorOut, LOW);
  return value;
}

void sortObject(int binNumber) {
  setAllGatesClosed();

  switch (binNumber) {
    case 1:
      gate1.write(GATE_OPEN);
      break;
    case 2:
      gate2.write(GATE_OPEN);
      break;
    case 3:
      gate3.write(GATE_OPEN);
      break;
    case 4:
      gate4.write(GATE_OPEN);
      break;
    case 5:
      gate5.write(GATE_OPEN);
      break;
    default:
      break;
  }

  delay(SORTING_DELAY);
  setAllGatesClosed();
}

void setAllGatesClosed() {
  gate1.write(GATE_CLOSED);
  gate2.write(GATE_CLOSED);
  gate3.write(GATE_CLOSED);
  gate4.write(GATE_CLOSED);
  gate5.write(GATE_CLOSED);
  delay(120);
}
