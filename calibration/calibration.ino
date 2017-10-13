//Define all the components. Sensors, motors, and some meanings are declared.
#define SENSOR_L A0
#define SENSOR_R A1
#define MOTOR_L 3
#define MOTOR_R 4
#define FWD 1
#define BWD 2
#define SUPPLY_VOLTAGE 11.2

String prefix = "";

void setup() {
  // put your setup code here, to run once:
  // Open serial communications
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Take data at the left and right sensors
  int reading = analogRead(SENSOR_L);
  int rR = analogRead(SENSOR_R);
  // Print both readings to the serial monitor
  Serial.println(prefix + "Left: " + reading + " Right: " + rR);
  // Loop at less than max speed
  delay(20);
}


