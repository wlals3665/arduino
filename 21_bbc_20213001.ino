
#include <Servo.h>

 

// Arduino pin assignment

#define PIN_IR A0

#define PIN_LED 

#define PIN_SERVO 10

 

Servo myservo;

 

int a, b; // unit: mm

 

void setup() {

// initialize serial port

  myservo.attach(PIN_SERVO);

  myservo.writeMicroseconds(1310);

  delay(1000);

  Serial.begin(57600);

  

  a = 76; //70;

  b = 385; //300;

}

 

float ir_distance(void){ // return value unit: mm

  float val;

  float volt = float(analogRead(PIN_IR));

  val = ((6762.0/(volt-9.0))-4.0) * 10.0;

  return val;

}

 

void loop() {

  float raw_dist = ir_distance();

  float dist_cali = 100 + 300.0 / (b - a) * (raw_dist - a);

  Serial.print("min:0,max:500,dist:");

  Serial.print(raw_dist);

  Serial.print(",dist_cali:");

  Serial.println(dist_cali);

  if(raw_dist>210) { // 거리가 255이상일때 레일판 올리기

    myservo.writeMicroseconds(1000); //e

    delay(100);

  }

  else if (raw_dist<210) { // 거리가 255이하일때 레일판 내리기

    myservo.writeMicroseconds(1600);  //f

    delay(100); 

  }

}
