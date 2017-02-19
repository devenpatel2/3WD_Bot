#include <Steering.h>

#include <ros.h>
#include <std_msgs/Int16.h>


#define EncoderSlots 20

//RIGHT MOTOR
#define E1 10  // Enable Pin for motor 1
#define I1 8  // Control pin 1 for motor 1
#define I2 9  //   Control pin 2 for motor 1
#define RightEncoderPin 2

//LEFT MOTOR
#define E2 11  // Enable Pin for motor 2
#define I3 6  // Control pin 1 for motor 2
#define I4 7  // Control pin 2 for motor 2
#define LeftEncoderPin 3
Steering::EncoderSettings enSettingsR = {RightEncoderPin, EncoderSlots};
Steering::EncoderSettings enSettingsL = {LeftEncoderPin, EncoderSlots};

Steering::MotorSettings mSettingsR = {E1, I1, I2};
Steering::MotorSettings mSettingsL = {E2, I3, I4};

Steering::Encoder encoderRight(enSettingsR);
Steering::Encoder encoderLeft(enSettingsL);

Steering::Motor motorRight(mSettingsR, enSettingsR);
Steering::Motor motorLeft(mSettingsL, enSettingsL);

ros::NodeHandle  nh;

std_msgs::Int16 encoderMsgL;
std_msgs::Int16 encoderMsgR;
ros::Publisher pubEncoderRight("encoder/right" ,  &encoderMsgR);
ros::Publisher pubEncoderLeft("encoder/left" ,  &encoderMsgL);
bool forward = true;
volatile int countL = 0;
volatile int countR = 0;
unsigned long previousMillis = 0;     
const long interval = 10000;           
void setup()
{ 
    attachInterrupt(0, encoderRightISR, CHANGE); 
    attachInterrupt(1, encoderLeftISR, CHANGE); 
    nh.initNode();
    nh.advertise(pubEncoderRight);
    nh.advertise(pubEncoderLeft); 

}

void loop(){
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {        
        previousMillis = currentMillis; 
        if (forward){
            motorRight.forward();
            motorLeft.forward();
            forward = false;
        }
        else {
            motorLeft.reverse();
            motorRight.reverse();
            forward = true;
        }
    }
    countR = encoderRight.getCount();
    encoderMsgR.data = countR;
    pubEncoderRight.publish(&encoderMsgR);

    countL = encoderLeft.getCount();
    encoderMsgL.data = countL;
    pubEncoderLeft.publish(&encoderMsgL);

    nh.spinOnce();
    delay(10);
    
}

void encoderRightISR()
{
    encoderRight.isr();
}

void encoderLeftISR()
{
    encoderLeft.isr();
}
