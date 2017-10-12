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
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = analogRead(SENSOR_L);
  int rR = analogRead(SENSOR_R);
  Serial.println(prefix + "Left: " + reading + " Right: " + rR);
  delay(20);
}


