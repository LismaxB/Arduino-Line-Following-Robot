// Line Following Robot using Arduino

// Pin Definitions
const int leftSensorPin = A0;    // Analog pin for left sensor
const int centerSensorPin = A1;  // Analog pin for center sensor
const int rightSensorPin = A2;   // Analog pin for right sensor
const int leftMotorPin1 = 2;     // Pin for left motor control
const int leftMotorPin2 = 3;     // Pin for left motor control
const int rightMotorPin1 = 4;    // Pin for right motor control
const int rightMotorPin2 = 5;    // Pin for right motor control

// Sensor Thresholds
const int threshold = 500;       // Threshold for detecting the line

// Motor Speeds
const int leftMotorSpeed = 180;  // Speed of the left motor
const int rightMotorSpeed = 180; // Speed of the right motor

// Function to move the robot forward
void moveForward() {
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
}

// Function to stop the robot
void stopRobot() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
}

// Function to adjust the robot's movement based on sensor readings
void adjustMovement(int left, int center, int right) {
  if (left < threshold && center < threshold && right < threshold) {
    // All sensors off the line, stop the robot
    stopRobot();
  } else if (left > threshold && center < threshold && right > threshold) {
    // Line in the center, move forward
    moveForward();
  } else if (left < threshold && center > threshold && right < threshold) {
    // Line in the center, move forward
    moveForward();
  } else if (left < threshold && center < threshold && right > threshold) {
    // Line on the left, adjust movement to the right
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  } else if (left > threshold && center < threshold && right < threshold) {
    // Line on the right, adjust movement to the left
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }
}

// Setup function
void setup() {
  // Initialize motor control pins as outputs
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  // Set initial motor speed and direction
  analogWrite(leftMotorPin1, leftMotorSpeed);
  analogWrite(leftMotorPin2, LOW);
  analogWrite(rightMotorPin1, rightMotorSpeed);
  analogWrite(rightMotorPin2, LOW);
  
  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int leftSensorValue = analogRead(leftSensorPin);
  int centerSensorValue = analogRead(centerSensorPin);
  int rightSensorValue = analogRead(rightSensorPin);
  
  // Print sensor values for debugging
  Serial.print("Left: ");
  Serial.print(leftSensorValue);
  Serial.print(", Center: ");
  Serial.print(centerSensorValue);
  Serial.print(", Right: ");
  Serial.println(rightSensorValue);
  
  // Adjust robot's movement based on sensor readings
  adjustMovement(leftSensorValue, centerSensorValue, rightSensorValue);
}
