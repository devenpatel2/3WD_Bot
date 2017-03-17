#include <Steering.h>
#include <Utils/utils.h>
#include <ros.h>
#include <std_msgs/Float32.h>
/*
#include<tf/tf.h>
#include <geometry_msgs/Pose.h>
*/
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

float wheelRadius = 3.25;
float axleTrack = 14.5; 
Steering::Wheel wheelRight(wheelRadius, mSettingsR, enSettingsR);
Steering::Wheel wheelLeft(wheelRadius, mSettingsL, enSettingsL);

Steering::Steer steer(axleTrack, wheelLeft, wheelRight);
ros::NodeHandle  nh;
std_msgs::Float32 headingMsg;
ros::Publisher pubHeading("heading" ,  &headingMsg);
ros::Publisher pubLeftDistance("left/distance" ,  &headingMsg);
ros::Publisher pubRightDistance("right/distance" ,  &headingMsg);
const long interval = 2000;           
long int previousTime = 0;           
/*
geometry_msgs::Pose poseMsg;

ros::Publisher pubPose("odom" , &poseMsg); 
bool forward = true;
unsigned long previousMillis = 0;     

void publishPoseMsg(const Steering::Pose &pose);
float distance_L = 0;
float distance_R = 0;
float currentHeading = 0;
Steering::Pose pose ; 
*/
void setup()
{ 
    //Interrupt Setup
    
    attachInterrupt(0, encoderRightISR, CHANGE); 
    attachInterrupt(1, encoderLeftISR, CHANGE); 
    //Ros setup
    nh.initNode();
    nh.advertise(pubHeading);
    nh.advertise(pubLeftDistance); 
    nh.advertise(pubRightDistance); 
    /*
    nh.advertise(pubPose);
    */
}

void loop(){
	    
	Steering::Pose pose; 
    if(millis() - previousTime > interval){
		steer.maintainHeading(0.0);
    //steer.forward(150);
	pose = steer.getPose();
    
    //publishPoseMsg(pose); 
    headingMsg.data = steer.getDiff();//pose.theta * (180/M_PI); 
    pubHeading.publish(&headingMsg);
    
    headingMsg.data = wheelLeft.distance();   
    pubLeftDistance.publish(&headingMsg);

    headingMsg.data = wheelRight.distance();   
    pubRightDistance.publish(&headingMsg);

		previousTime = millis();
	}

    /*
    //distanceMsg.data = wheelLeft.distance();
    //pubLeftWheel.publish(&distanceMsg);

    */
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
/*
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
*/
