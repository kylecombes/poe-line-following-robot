int delayTime = 1000;
byte delayByte = 1;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
 
 if (Serial.available());{
  Serial.println("Checking.");
  delayByte = Serial.read();
  Serial.print("Recieved: ");
  Serial.println(delayByte);

  delayTime = delayByte*500;
  if (delayTime < 100); {
    delayTime = 100;
  }
    
  
  delay(delayTime);                       // wait for a second
  digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off by making the voltage LOW
  delay(delayTime);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)

  }
}
