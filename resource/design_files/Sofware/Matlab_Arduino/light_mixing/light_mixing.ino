/*
 * Light Mixing
 * Serial Communication with Matlab
*/
#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_TCS34725.h>

/*Hardware setup*/
/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */
//LED pins
#define redpin 3
#define greenpin 5
#define bluepin 6
#define amberpin 9
#define purplepin 10
#define whitepin 11

//RGB sensor & interrupt
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
const int interruptPin = 2;

//program values
int red, green, blue, amber, purple, white;
volatile boolean state = false;

//Serial communication
String scmd;
float input;

/*------------------------sensor-------------------------------------*/
/* tcs.getRawData() does a delay(Integration_Time) after the sensor readout.
  We don't need to wait for the next integration cycle because we receive an interrupt when the integration cycle is complete*/
void getRawData_noDelay()
{
  uint16_t r, g, b, c;  //calibration
  c = tcs.read16(TCS34725_CDATAL);
  r = tcs.read16(TCS34725_RDATAL);
  g = tcs.read16(TCS34725_GDATAL);
  b = tcs.read16(TCS34725_BDATAL);
  //serial send duty cycle info
  Serial.print("sensor output|");
  Serial.print("r="); Serial.print(r); Serial.print("|");
  Serial.print("g="); Serial.print(g); Serial.print("|");
  Serial.print("b="); Serial.print(b); Serial.print("|");
  Serial.print("c="); Serial.print (c); Serial.print("|\n");
  delay(2000);
}
/*------------------------end of sensor ----------------------------*/
/*---------------------------custom functions---------------------------*/

void fntest() {
  Serial.println("true");
  digitalWrite(13, LOW);
}

void fnset( char c, int pwm) {
  digitalWrite(13, HIGH);
  switch (c) {
    case 'r':
      analogWrite(redpin, pwm);
      red = pwm;
      Serial.println("set red");
      break;
    case 'g':
      analogWrite(greenpin, pwm);
      green = pwm;
      Serial.println("set green");
      break;
    case 'b':
      analogWrite(bluepin, pwm);
      blue = pwm;
      Serial.println("set blue");
      break;
    case 'a':
      analogWrite(amberpin, pwm);
      amber = pwm;
      Serial.println("set amber");
      break;
    case 'p':
      analogWrite(purplepin, pwm);
      purple = pwm;
      Serial.println("set purple");
      break;
    case 'w':
      analogWrite(whitepin, pwm);
      white = pwm;
      Serial.println("set white");
      break;
    default:
      Serial.println((String)c + " no such color");
      break;
  }
  delay(1000);
}


void fnget( char c) {
  switch (c) {
    case 'r':
      Serial.print("r="); Serial.print(red); Serial.println(" ");
      break;
    case 'g':
      Serial.print("g="); Serial.print(green); Serial.println(" ");
      break;
    case 'b':
      Serial.print("b="); Serial.print(blue); Serial.println(" ");
      break;
    case 'a':
      Serial.print("a="); Serial.print(amber); Serial.println(" ");
      break;
    case 'p':
      Serial.print("p="); Serial.print(purple); Serial.println(" ");
      break;
    case 'w':
      Serial.print("w="); Serial.print(white); Serial.println(" ");
      break;
    default:
      Serial.println((String)c + " no such color");
      break;
  }
  delay(1000);
}

void getLED() {
  //serial send duty cycle info
  Serial.print("calibration duty cycles|");
  Serial.print("r="); Serial.print(red); Serial.print("|");
  Serial.print("g="); Serial.print(green); Serial.print("|");
  Serial.print("b="); Serial.print(blue); Serial.print("|");
  Serial.print("a="); Serial.print (amber); Serial.print("|");
  Serial.print("p="); Serial.print( purple ); Serial.print("|");
  Serial.print("w="); Serial.print(white); Serial.print("|");
  Serial.println(" ");
  delay(2000); //2 seconds for serial
}
void randLED() {
  //generate random input
  red = random(0, 255 * 0.6); green = random(0, 255 * 0.9); blue = random(0, 255 * 0.95);
  amber = random(0, 255 * 0.65); purple = random(0, 255); white = random(0, 255 * 0.9);

  //assign duty cycles
  analogWrite(redpin, red); analogWrite(greenpin, green); analogWrite(bluepin, blue);
  analogWrite(amberpin, amber); analogWrite(purplepin, purple); analogWrite(whitepin, white);
  getLED();
}
/*---------------------------end of custom functions--------------------------------*/
void setup() {
  Serial.begin(9600); //Serial

  //onboard LED for test
  pinMode(13, OUTPUT); digitalWrite(13, HIGH);

  // LED pin output and values
  pinMode(redpin, OUTPUT); pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT); pinMode(amberpin, OUTPUT);
  pinMode(purplepin, OUTPUT); pinMode(whitepin, OUTPUT);
  red = 0; green = 0; blue = 0; amber = 0; purple = 0; white = 0;

  //sensor finding
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Set persistence filter to generate an interrupt for every RGB Cycle, regardless of the integration limits
  tcs.write8(TCS34725_PERS, TCS34725_PERS_NONE);
  tcs.setInterrupt(true); //turn off light

  //Serial ready
  Serial.println("Ready");
  Serial.flush();
}

void loop() {
  String cmd; int index1 = 0; int index2 = 0; //command parsing

  //Serial communication
  if (Serial.available()) {
    scmd = Serial.readString();
    scmd.trim();
    if (scmd.equals("test")) {
      fntest();
    } else if (scmd.equals("rand")) {
      randLED();
    } else if (scmd.equals("getsensor")) {
      getRawData_noDelay();
    } else if (scmd.equals("getLED")) {
      getLED();
    } else {
      //command parsing
      index1 = scmd.indexOf(' ');
      index2 = scmd.indexOf('=');
      cmd = scmd.substring(0, index1);
      cmd.trim();
      if (cmd.equals("set")) {
        fnset( scmd.charAt(index1 + 1), scmd.substring(index2 + 1).toInt());
      } else if (cmd.equals("get")) {
        fnget( scmd.charAt(index1 + 1));
      } else {
        Serial.println("Available commands: test, rand, getsensor, getLED, set color=int, get color=");
      }
      delay(100);
      Serial.flush();
    }
  }
}
