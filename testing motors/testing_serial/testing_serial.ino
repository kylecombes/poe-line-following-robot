int delayTime = 1000;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  String command;

  if (Serial.available() > 0) {
    Serial.println("Checking.");
    command = Serial.readString();
    Serial.println("Command recieved:" + command);
    delayTime = command.toInt();
    Serial.println(delayTime+1);
    
//    delayTime = Serial.parseInt() * 100;
//    Serial.print("Recieved: ");
//    Serial.println(delayTime);

    if (delayTime < 100) {
      delayTime = 1000;
    }
  }


  delay(delayTime);                       // wait for a second
  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
  delay(delayTime);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)

}
