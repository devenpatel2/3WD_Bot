#include <Steering.h>

#include <ros.h>
#include<tf/tf.h>
#include <geometry_msgs/Pose.h>
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
float axleTrack = 10.0; 
Steering::Wheel wheelRight(wheelRadius, mSettingsR, enSettingsR);
Steering::Wheel wheelLeft(wheelRadius, mSettingsL, enSettingsL);

Steering::Steer steer(axleTrack, wheelLeft, wheelRight);
Steering::Pose pose; 

ros::NodeHandle  nh;
geometry_msgs::Pose poseMsg;
std_msgs::Float32 distanceMsg;

ros::Publisher pubRightWheel("right/distance" ,  &distanceMsg);
ros::Publisher pubLeftWheel("left/distance" , &distanceMsg);
ros::Publisher pubPose("odom" , &poseMsg); 

bool forward = true;
unsigned long previousMillis = 0;     
const long interval = 2000;           

void publishPoseMsg(const Steering::Pose &pose);

void setup()
{ 
    //Interrupt Setup
    
    attachInterrupt(0, encoderRightISR, CHANGE); 
    attachInterrupt(1, encoderLeftISR, CHANGE); 
    
    //Ros setup
    nh.initNode();
    nh.advertise(pubPose);
    //nh.advertise(pubRightWheel);
    //nh.advertise(pubLeftWheel); 

}

void loop(){
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {        
        previousMillis = currentMillis; 
        if (forward){
            steer.stop();            
            delay(5);
            steer.left();         
            forward = false;
        }
        else {
            steer.stop();           
            delay(5);
            steer.right();           
            forward = true;
        }
    }
    pose = steer.getPose();
    publishPoseMsg(pose); 
    
    //distanceMsg.data = wheelRight.distance();
    //pubRightWheel.publish(&distanceMsg);

    //distanceMsg.data = wheelLeft.distance();
    //pubLeftWheel.publish(&distanceMsg);

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

void publishPoseMsg(const Steering::Pose &pose){
    
    //Euler angle to Quaternion 
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionFromYaw(pose.theta);

    //set the position
    poseMsg.position.x = pose.x;
    poseMsg.position.y = pose.y;
    poseMsg.orientation = odom_quat;

    //publish the message
    pubPose.publish(&poseMsg);
}
