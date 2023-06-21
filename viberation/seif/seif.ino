const int vibrationPin = 25; // replace 2 with the digital pin number where the vibration sensor is connected
const int threshold = 7; // set the threshold value for vibration detection
int flag;
void setup() {
  pinMode(vibrationPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = digitalRead(vibrationPin);

  if (sensorValue == HIGH) {
    // If sensor reads high, check if it is a shaking or a movement
    int count = 0;
    for (int i = 0; i < 10; i++) { // check for 10 consecutive readings
      if (digitalRead(vibrationPin) == HIGH) {
        count++;
      }
      delay(5);
    }
    if (count >= threshold) {
      // If at least threshold consecutive readings are high, turn on the LED
      flag++;
    } else {
      // If less than threshold consecutive readings are high, turn off the LED
     
    }
  } else {
    // If sensor reads low, turn off the LED
   
  }
  if(flag==10)
  {
    Serial.println("danger");
    flag=0;
  }
}
