#include <basicMPU6050.h>
#include <Wire.h>

const int MPU_addr=0x68; // The MPU sensor I2C address
float x;
float y;
float z;
float newX;

float CENTER;

bool left, right;
bool center = true;

//float X_out, Y_out, Z_out;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  //   PWR_MGMT_1 register
  Wire.write(0x00);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  //steering(newX);
}

int  x_out = 0;
void loop() {
  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);  // request a total of 14 registers

  x = (Wire.read()<<8|Wire.read())/256, BIN; // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)  (+60 to 0 to -60)  
  y = Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  z = Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

 //Serial.println(x, BIN); // convert float to a binary value

 
 //Serial.println(x);

 //left
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
 
   Serial.flush();
   Serial.println(x_out);
   delay(80);
}
