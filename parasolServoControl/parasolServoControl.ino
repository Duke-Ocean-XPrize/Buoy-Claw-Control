//JONAH T. WAHL
//Program to control parasol system from pixhawk or radio

//get servo library and create a variable for raw data switch pin
#include <Servo.h>
byte SWITCH = 3;

//create a servo object
Servo parasolA;
Servo parasolB;

//create a variable to hold raw data value from SWITCH
float switch_val;

void setup() {
  //set raw data SWITCH pin to input
  pinMode(SWITCH, INPUT);

  //set servo object to value on pin 10
  parasolA.attach(10);
  parasolB.attach(6);
  Serial.begin(115200);
}

//specify telemetry data ranges
const int min_micros = 1000;                                        
const int max_micros = 2000;

void loop() {
  switch_val = pulseIn(SWITCH, HIGH);                               //get the value from the switch

  //2-STATE CONTROL
  if (switch_val <= ((min_micros + max_micros)/2)) {              //map raw data to two possible servo angles
    parasolA.write(180);                                             //write max angle to servo object
    parasolB.write(0);
  }
  else {
    parasolA.write(0);                                               //write min angle to servo object
    parasolB.write(180);
  }

  //VARIABLE CONTROL
  /*float switch_f = ((switch_val - min_micros)/(min_micros/180));    //map raw data to servo angles
  parasolA.write(switch_f);                                          //write corresponding angle to servo object
  parasolB.write(-switch_f);

  //output raw data followed by angle to monitor
  Serial.print("PWM: ");
  Serial.print(switch_val);
  Serial.print(", DEGREES: ");
  Serial.println(switch_f);*/
}
