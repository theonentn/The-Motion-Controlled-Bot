#include<Wire.h>
#include<ADXL345.h>
# define Ln 7
# define Lp 4
# define El 5  //pwm pin for left motor
# define Rn 8 
# define Rp 12
# define Er 6  //pwm pin for right motor

ADXL345 adxl;   //adxl 

int x,y,z;
int rawx,rawy,rawz;
int mappedRawX,mappedRawY,mappedRawZ;

void setup()
{  
  Serial.begin(9600);  
  pinMode(Lp, OUTPUT);  
  pinMode(Ln, OUTPUT);  
  pinMode(El, OUTPUT);  
  pinMode(Rp, OUTPUT);  
  pinMode(Rn, OUTPUT);
  pinMode(Er, OUTPUT);     
  analogWrite(El, 255);     //speed of left motor 
  analogWrite(Er, 255);     //speed of right motor

 adxl.powerOn();      // from library
  }

  void loop()
  {
    
  adxl.readAccel(&x,&y,&z);
  rawx=x-7;
  rawy=y-6;
  rawz=z+10;
  if(rawx<-255)rawx=-255;else if(rawx>255)rawx=255;
   if(rawy<-255)rawy=-255;else if(rawy>255)rawy=255;
   if(rawz<-255)rawz=-255;else if(rawz>255)rawz=255; // u can use the constrain keyword 
   mappedRawX=map(rawx,-255,255,0,180); 
   mappedRawY=map(rawy,-255,255,0,180); 
   mappedRawZ=map(rawz,-255,255,0,180);
   
Serial.print("mappedRawX =");Serial.println(mappedRawX);
Serial.print("mappedRawY =");Serial.println(mappedRawY);
//Serial.print("mappedRawZ =");Serial.println(mappedRawZ);
  if(50 <= mappedRawX && mappedRawX <= 110 && 50 <= mappedRawY && mappedRawY <= 110) //range of adxl for which the car remains stationary
  {
    MotorControl(0,0);
    Serial.println("STAY");
  }
    if( 0 <= mappedRawY && mappedRawY <= 50)
  {
    MotorControl(2,1);
        Serial.println("LEFT");
  }
  if(110 < mappedRawY && mappedRawY <= 180)
  {
    MotorControl(1,2);
        Serial.println("RIGHT");
  } 
  if(0 < mappedRawX && mappedRawX < 50 )
  {
    MotorControl(1,1);
        Serial.println("FORWARD");
  }
 
   if(110 < mappedRawX && mappedRawX<180)
  {
    MotorControl(2,2);
      Serial.println("BACKWARD");
  }
  
// delay(1900);                       
 }

void MotorControl(int driveL, int driveR)
{
//Motorcontrol: Controlling the motors. In this case, 2 motors used

  switch(driveL)  
  {   //left motor
  case 0:    digitalWrite(Ln, LOW);    digitalWrite(Lp, LOW);    break;     //motor stops
  case 1:    digitalWrite(Ln, LOW);    digitalWrite(Lp, HIGH);    break;    // motor in forward direction   
  case 2:    digitalWrite(Ln, HIGH);    digitalWrite(Lp, LOW);    break;    // motor in backward direction
  default: break;  
  }  
  switch(driveR)
  {   //right motor
    case 0:    digitalWrite(Rn, LOW);    digitalWrite(Rp, LOW);    break;       //motor stops
    case 1:    digitalWrite(Rn, LOW);    digitalWrite(Rp, HIGH);    break;      // motor in forward direction  
    case 2:    digitalWrite(Rn, HIGH);    digitalWrite(Rp, LOW);    break;     // motor in backward direction
    default: break;   
    }
    }
