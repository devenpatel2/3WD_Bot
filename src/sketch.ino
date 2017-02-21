#include <Steering.h>

#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>


#define EncoderSlots 20

//RIGHT MOTOR
#define E1 10  // Enable Pin for wheel 1
#define I1 8  // Control pin 1 for wheel 1
#define I2 9  //   Control pin 2 for wheel 1
#define RightEncoderPin 2

//LEFT MOTOR
#define E2 11  // Enable Pin for wheel 2
#define I3 6  // Control pin 1 for wheel 2
#define I4 7  // Control pin 2 for wheel 2
#define LeftEncoderPin 3


Steering::EncoderSettings enSettingsR = {RightEncoderPin, EncoderSlots};
Steering::EncoderSettings enSettingsL = {LeftEncoderPin, EncoderSlots};

Steering::MotorSettings mSettingsR = {E1, I1, I2};
Steering::MotorSettings mSettingsL = {E2, I3, I4};

float wheelRadius = 3.5;
Steering::Wheel wheelRight(wheelRadius, mSettingsR, enSettingsR);
Steering::Wheel wheelLeft(wheelRadius, mSettingsL, enSettingsL);

ros::NodeHandle  nh;

std_msgs::Int16 encoderMsg;
std_msgs::Float32 distanceMsg;

ros::Publisher pubRightEncoder("right/encoder" ,  &encoderMsg);
ros::Publisher pubLeftEncoder("left/encoder" ,  &encoderMsg);
ros::Publisher pubRightWheel("right/distance" ,  &distanceMsg);
ros::Publisher pubLeftWheel("left/distance" ,  &distanceMsg);

bool forward = true;
volatile int countL = 0;
volatile int countR = 0;
unsigned long previousMillis = 0;     
const long interval = 2000;           
void setup()
{ 
    attachInterrupt(0, encoderRightISR, CHANGE); 
    attachInterrupt(1, encoderLeftISR, CHANGE); 
    nh.initNode();
    nh.advertise(pubRightEncoder);
    nh.advertise(pubLeftEncoder); 
    nh.advertise(pubRightWheel);
    nh.advertise(pubLeftWheel); 


}

void loop(){
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {        
        previousMillis = currentMillis; 
        if (forward){
            wheelRight.stop();
            wheelLeft.stop();
            delay(5);
            wheelRight.forward();
            wheelLeft.forward();
            forward = false;
        }
        else {
            
            wheelRight.stop();
            wheelLeft.stop();
            delay(5);
            wheelLeft.reverse();
            wheelRight.reverse();
            forward = true;
        }
    }
    encoderMsg.data = wheelRight.encoder->count();
    pubRightEncoder.publish(&encoderMsg);

    encoderMsg.data = wheelLeft.encoder->count();
    pubLeftEncoder.publish(&encoderMsg);

    distanceMsg.data = wheelRight.distance();
    pubRightWheel.publish(&distanceMsg);

    distanceMsg.data = wheelLeft.distance();
    pubLeftWheel.publish(&distanceMsg);


    nh.spinOnce();
    delay(10);
    
}

void encoderRightISR()
{
    wheelRight.encoder->isr();
}

void encoderLeftISR()
{
    wheelLeft.encoder->isr();
}
