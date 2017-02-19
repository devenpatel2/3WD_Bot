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
#define I3 12  // Control pin 1 for motor 2
#define I4 13  // Control pin 2 for motor 2
#define LeftEncoderPin 3

Steering::EncoderSettings enSettingsR = {RightEncoderPin, EncoderSlots};
Steering::EncoderSettings enSettingsL = {LeftEncoderPin, EncoderSlots};

Steering::Encoder encoderRight(enSettingsR);
Steering::Encoder encoderLeft(enSettingsL);

ros::NodeHandle  nh;

std_msgs::Int16 encoderMsg;
ros::Publisher pubEncoderRight("encoder/right" ,  &encoderMsg);
ros::Publisher pubEncoderLeft("encoder/left" ,  &encoderMsg);


int count = 0;
void setup()
{ 
    attachInterrupt(0, encoderRightISR, CHANGE); 
    attachInterrupt(1, encoderLeftISR, CHANGE); 
    nh.initNode();
    nh.advertise(pubEncoderRight);
    nh.advertise(pubEncoderLeft); 
}

void loop(){
  
    count = encoderLeft.getCount();
    encoderMsg.data = count;
    pubEncoderLeft.publish(&encoderMsg);

    count = encoderRight.getCount();
    encoderMsg.data = count;
    pubEncoderRight.publish(&encoderMsg);    
    
    nh.spinOnce();
    delay(10);

}

void encoderRightISR()
{
    encoderRight.isr();
}

void encoderLeftISR()
{
    encoderRight.isr();
}
