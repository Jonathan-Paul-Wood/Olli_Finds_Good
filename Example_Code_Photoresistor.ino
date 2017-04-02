//KY018 Photo resistor module
 
int sensorPin = A5; // select the input pin for the potentiometer
int movingLed = 6; // select the pin for the LED
int stoppedLed = 7;
int buttonPin = 2; // select pin for button
int sensorValue = 0; // variable to store the value coming from the sensor
int rw = 0; //indicates whether or not to read or write - 0 = read, 1 = write
int button_previous = LOW;
int mode = 0; // 0 is stopped, 1 is moving bus
int checked = 0; //starts not checked
int buttonLock = 0; //for debouncing
int printed = 1;
void setup() {
  pinMode(movingLed, OUTPUT);
  pinMode(stoppedLed, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}
void loop() {
  if(mode == 1){ //bus in motion
    digitalWrite(movingLed, HIGH);
    digitalWrite(stoppedLed, LOW);
   //do nothing if bus is in motion
  }else if(mode == 0){ //bus stopped
    digitalWrite(movingLed, LOW);
    digitalWrite(stoppedLed, HIGH);
    if(!checked){ //wait four seconds then check seat
      sensorValue = analogRead(sensorPin);
      //Serial.println(sensorValue);
      if(sensorValue < 250){
        checked = 1;
      }
    }else{
      if(!printed){
      delay(2000);
      Serial.println("1");
      printed = 1;
      }else{
        
      }
      //do nothing check complete
    }
  }

  int var = digitalRead(buttonPin);
  if(var && !buttonLock){ // switch modes
      if(mode == 0){
        printed = 0;
        checked = 0;
        mode = 1;
      }else{
        mode = 0;
      }
      buttonLock = 1;
    }

    if(!var && buttonLock){
      delay(50);
      buttonLock = 0;
    }
    delay(100);
}
