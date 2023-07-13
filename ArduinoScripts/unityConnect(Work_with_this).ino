#include <SerialCommand.h>
#include <Wire.h>
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#define PulseWire A0
//  Variables
//const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED = LED_BUILTIN;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;    
int x_out = 0;  
String steer;
PulseSensorPlayground pulseSensor;

#define FORCE_SENSOR_PIN A1
int fsr = 0; //pressure sensor value variable

const int MPU_addr=0x68; // The MPU sensor I2C address
float x;//gyro scope x axis variable
float y;
float z;

bool left, right;
bool center = true;
int myBPM, newBPM;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  //   PWR_MGMT_1 register
  Wire.write(0x00);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  //pulse....
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
  
   //while (!Serial) {
   // ; // wait for serial port to connect. Needed for native USB port only
   // }
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
   //establishContact();
}

// the loop function runs over and over again forever
void loop() {

    combinedValues();
  
  if (Serial.available()){
    char c = Serial.read();

  
    if(c == 'A'){
     // digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("on"); 
      //delay(1000);
    }
    else if(c == 'Z'){
    //    digitalWrite(LED_BUILTIN, LOW);
        Serial.println("off"); 
        //delay(1000);
    }
    c == NULL;
  
  }
     // turn the LED on (HIGH is the voltage level)
                // wait for a second
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('b');   // send a capital A
    delay(300);
  }
  
}
void fsrLed(){
  int temp = analogRead(FORCE_SENSOR_PIN);
  fsr = map(temp, 1023,0,0,255);
  //fsr = map(FORCE_SENSOR_PIN, 1023, 0, 0, 255);
  
 // Serial.print("Sensor: ");
  Serial.println(fsr);

  //led conditions
  if(fsr > 50){
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);                       
  digitalWrite(LED_BUILTIN, LOW);    
  delay(100); 
  }else{  
    digitalWrite(LED_BUILTIN, LOW);  
  }
}


void gyroSteer(){    
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 14, true);  // request a total of 14 registers
  
    x = (Wire.read()<<8|Wire.read())/256, BIN; // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)  (+60 to 0 to -60)  
    y = Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    z = Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
   //Serial.println(x, BIN); // convert float to a binary value
  
   //deadzone range -20<x<20 
   if(x>20){
     left = true;
     right = false;
     center = false;
     steer = "left";
    // Serial.println("left");
   }
   if(x<-20){
     right = true;
     left =  false;
     center = false;
     steer = "right";
   //  Serial.println("right");
   }
   if(x<20 && x>-20){
     center = true;
     left = false;
     right = false;
     steer = "cener";
     Serial.println("center");
   }

  // Serial.println(steer);
}

void combinedValues(){
//pulse Logic

     if (pulseSensor.sawStartOfBeat()) {        // Constantly test to see if "a beat happened".
       myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".                                           // "myBPM" hold this BPM value now. 
       
      // Serial.print("♥ A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
       //  Serial.print("BPM: ");                        // Print phrase "BPM: " 
     //  Serial.println(myBPM);                        // Print the value inside of myBPM. 
     }
     delay(20);

//force sensor logic
  int temp = analogRead(FORCE_SENSOR_PIN);
  fsr = map(temp, 1023,0,0,255);
  //fsr = map(FORCE_SENSOR_PIN, 1023, 0, 0, 255);
  
 // Serial.print("Sensor: ");
  //Serial.println(fsr);

  //led conditions
  /*
   * if(fsr > 50){
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);                       
  digitalWrite(LED_BUILTIN, LOW);    
  delay(100); 
  }else{  
    digitalWrite(LED_BUILTIN, LOW); 
*/
//Gyrscope logic
 Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 14, true);  // request a total of 14 registers
  
    x = (Wire.read()<<8|Wire.read())/256, BIN; // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)  (+60 to 0 to -60)  
    y = Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    z = Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
   //Serial.println(x, BIN); // convert float to a binary value
  
   //deadzone range -20<x<20 
  if(x>20){
   x_out = -1;
   //Serial.flush();
   //Serial.println("-1");
   //delay(80);
 }
 if(x<-20){
   x_out = 1;
   //Serial.flush();
   //Serial.println("1");
   //delay(80);
 }
 if(x<20 && x>-20){

   x_out = 0;
   //Serial.flush();
   //Serial.println("0");
   //delay(80);
 }
 



   

    // Serial.flush();
     Serial.print(fsr);
     Serial.print(" ");
     Serial.print(x_out);
     Serial.print(" ");
     Serial.print(myBPM);
     Serial.print(" ");
     Serial.println(x);
     delay(80);
     //delay(20);
     //.println( );
}  
