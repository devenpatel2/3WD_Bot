#include "Steer.h"
#include "Wheel.h"
#include <math.h>
#include "Utils/utils.h"

namespace Steering{
    Steer::Steer(float axleTrack, const Wheel &leftWheel, const Wheel &rightWheel):
        m_axleTrack(axleTrack), m_leftWheel(leftWheel), m_rightWheel(rightWheel),
        m_previousPose{0.0f, 0.0f, 0.0f}, m_currentPose{0.0f , 0.0f, 0.0f},
        m_movingArray{0,0,0,0,0}, m_diff(0){
    
        }
    
    void Steer::forward(){
        m_rightWheel.forward();
        m_leftWheel.forward();
    }

    void Steer::forward(int speed){
         m_leftWheel.forward(speed);
        m_rightWheel.forward(speed);
    }

    void Steer::reverse(){
        m_leftWheel.reverse();
        m_rightWheel.reverse();
    }

    void Steer::reverse(int speed){
        m_leftWheel.reverse(speed);
        m_rightWheel.reverse(speed);
    }

    void Steer::stop(){
        m_leftWheel.stop();
        m_rightWheel.stop();
    }
    
    void Steer::left(){
        m_leftWheel.reverse();
        m_rightWheel.forward();
    }
    
    void Steer::right(){
        m_rightWheel.reverse();
        m_leftWheel.forward();
    }

    void Steer::left(int speed){
        m_leftWheel.reverse(speed);
        m_rightWheel.forward(speed);
    }
    
    void Steer::right(int speed){
        m_rightWheel.reverse(speed);
        m_leftWheel.forward(speed);
    }

    float Steer::deltaDistanceTravelled(){

        return (m_leftWheel.deltaDistance() + m_rightWheel.deltaDistance())/2;
        
    }

    Pose Steer::getPose(){
        ///Pose pose = {0,0,0};
        m_currentPose.theta = m_previousPose.theta + (m_rightWheel.distance() - m_leftWheel.distance())/m_axleTrack;
        // limit heading to -Pi <= heading < Pi
        if (m_currentPose.theta > M_PI)
            m_currentPose.theta -= 2 * M_PI;
        else if (m_currentPose.theta <= -M_PI)
            m_currentPose.theta += 2 * M_PI;
        
        m_currentPose.theta = m_movingAverage(m_currentPose.theta);
        m_currentPose.x = deltaDistanceTravelled()* sin(m_currentPose.theta) + m_previousPose.x;
        m_currentPose.y = deltaDistanceTravelled()* cos(m_currentPose.theta) + m_previousPose.y;
          
        //m_previousPose = m_currentPose;
        return m_currentPose;
    }
   
   float Steer::getDiff(){
        return m_diff;
   }
   void Steer::maintainHeading(float heading){
        
        float error = heading - getPose().theta ;
        float diff = 100* error/(M_PI) ;  
        if( diff < -50) diff = -50;
        if( diff > 50) diff = 50;
        float diff_l = 200 - diff ;  
        float diff_r = 200 + diff;
        m_diff = error;
        //if (error < 0){  //turn right
        //else{ //turn left
           m_leftWheel.forward(int(diff_l));
           m_rightWheel.forward(int(diff_r));
           
    }

    void Steer::goToAngle(float targetHeading){
        int gain = 0.5 ;
        float error = targetHeading - getPose().theta;

        if (error > M_PI)
            error -= 2 * M_PI;
        else if (error < -M_PI)
            error += 2 * M_PI;

        //Proportional controller
        int controlSpeed = MAX_SPEED - (int)(0.5 * m_abs(error)/MAX_ERROR  * MAX_SPEED);
        
        while(error > 10){
            if (error>0) 
                left(controlSpeed);
            else
                right(controlSpeed);
            
            error = targetHeading - getPose().theta;
        }
    
    }
    
    float Steer::m_abs(float value){
    
        return (value> 0) ? value : -1*value;
    }
   
    float Steer::m_movingAverage(float currentTheta){
   
        float tempStore, sum = 0;
        
        for(int i = 1; i<MA_LENGTH; i++){
            tempStore = m_movingArray[i];
            m_movingArray[i-1] = tempStore;
            sum += tempStore;   
        }
        m_movingArray[MA_LENGTH -1 ] = currentTheta ; 
        sum += currentTheta ; 
        return sum/MA_LENGTH;
    } 

 //namespace Steering
};
