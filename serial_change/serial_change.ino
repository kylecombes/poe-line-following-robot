// Setting up motors and motor shield
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define LEFT_WHEEL (1)  // this is the M1 pin on motor shield
#define RIGHT_WHEEL (2) // this is the M2 on motor shield
#define SENSOR_L A0 // left IR sensor pin
#define SENSOR_R A1 // right IR sensor pin
#define DEFAULT_PWM_SPEED 40 // the default speed to move the wheels at
#define PWM_DELTA 30 // the amount to increase a wheel by if its sensor sees the tape
#define DELAY_BTWN_READINGS 20 // ms to wait between IR readings and motor speed adjustments
#define IR_SENSOR_READING_COUNT 1 // number of readings to take and average before returning IR sensor reading value
#define TAPE_DETECTION_THRESHOLD 800 // IR sensor readings above this mean we're looking at black tape

//int DEFAULT_PWM_SPEED = 40; // the base wheel speed; no longer a constant.
String command; // will accept string input from serial monitor
//This should change with serial input. We'll see how it goes.

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Recognize the left and right wheels as DC motors
Adafruit_DCMotor *leftWheel = AFMS.getMotor(LEFT_WHEEL);
Adafruit_DCMotor *rightWheel = AFMS.getMotor(RIGHT_WHEEL);

long lastReadTime = 0; // Keep track of the last time a reading was made

void setup() {
  // put your setup code here, to run once:
  // Start serial monitor
  Serial.begin(9600);
  // Start talking to the motorshield
  AFMS.begin();  // create with the default frequency 1.6KHz
  Serial.println("Change base speed by typing in the Serial monitor. The default value is 30; inputting a non-integer will make the robot not turn");
//  Serial.println("Mass printing in order of:");
//  Serial.println("Time,   LSense,   RSense,   LMotor,   RMotor");
}

void loop() {
  // put your main code here, to run repeatedly:

//  // Adjust parameter based on serial input
//if (Serial.available() > 0){
//  Serial.print("Changing base Speed to:");
//  command = Serial.readString();
//  DEFAULT_PWM_SPEED = command.toInt();
//  Serial.println(DEFAULT_PWM_SPEED);
//}

  // Update the motor speeds
  long elapsedTime = millis() - lastReadTime;
  
  if (elapsedTime > DELAY_BTWN_READINGS) {
    // Read the IR sensors
    float leftSensorReading = readIRSensor(SENSOR_L);
    float rightSensorReading = readIRSensor(SENSOR_R);

    // Calculate wheel speeds based on IR readings
    // Reset the wheels to go straight
    int leftWheelSpeed = DEFAULT_PWM_SPEED;
    int rightWheelSpeed = DEFAULT_PWM_SPEED;

    // If the left sensor sees something, turn more left
    if (leftSensorReading > TAPE_DETECTION_THRESHOLD) {
//      leftWheelSpeed = -leftWheelSpeed;
      leftWheelSpeed -= PWM_DELTA;
      rightWheelSpeed += PWM_DELTA;
    }
    // If the right sensor sees something, turn more right
    // (Don't use an else here to avoid messing up at the perpendicular line on the track)
    if (rightSensorReading > TAPE_DETECTION_THRESHOLD) {
//      rightWheelSpeed = -rightWheelSpeed;
      leftWheelSpeed += PWM_DELTA;
      rightWheelSpeed -= PWM_DELTA;
    }

    // Run the wheels at the returned speed
    setWheelSpeed(LEFT_WHEEL, leftWheelSpeed);
    setWheelSpeed(RIGHT_WHEEL, rightWheelSpeed);

////Print everything to Serial for plotting
//Serial.print(millis());
//Serial.print("\t");
//Serial.print(leftSensorReading);
//Serial.print("\t");
//Serial.print(rightSensorReading);
//Serial.print("\t");
//Serial.print(leftWheelSpeed);
//Serial.print("\t");
//Serial.println(rightWheelSpeed);

    lastReadTime = millis();
  }
}

// Function to read and report from the sensors, averaged over multiple readings
float readIRSensor(int sensorId) { // Average over the course of multiple readings
  float total = 0;
  for (int readCount = 0; readCount < IR_SENSOR_READING_COUNT; ++readCount) {
    total += analogRead(sensorId);
    delay(5); // Delay for 10ms
  }
  return total / (float)IR_SENSOR_READING_COUNT;
}

// Function to run a wheel given a speed
void setWheelSpeed(int wheelId, int speed) {
  Adafruit_DCMotor* motor = (wheelId == LEFT_WHEEL) ? leftWheel : rightWheel;

  if (speed == 0) { // Just stop the motor and return
    motor->run(RELEASE);
    return;
  }
  
  int direction = FORWARD; // Default to going forward
  if (speed < 0) {
    speed = -speed;
    direction = BACKWARD; // Negative speed means we should go backward (not used currently)
  }
  if (speed > 255) { // Make sure our PWM isn't greater than 255
    speed = 255;
  }

  // Actually run the motors
  motor->setSpeed(speed); // Give the motor its speed
  motor->run(direction); // Run the motor (in the correct direction)
   
}



