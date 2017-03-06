#include "Steer.h"
#include "Wheel.h"
#include <math.h>
#include "Utils/utils.h"

namespace Steering{
    Steer::Steer(float axleTrack, const Wheel &leftWheel, const Wheel &rightWheel):
        m_axleTrack(axleTrack), m_leftWheel(leftWheel), m_rightWheel(rightWheel),
        m_previousPose{0.0f, 0.0f, 0.0f}, m_currentPose{0.0f , 0.0f, 0.0f}{
    
        }
    
    void Steer::forward(){
        m_leftWheel.forward();
        m_rightWheel.forward();
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
        
        m_currentPose.theta = m_previousPose.theta + (m_rightWheel.deltaDistance() - m_leftWheel.deltaDistance())/m_axleTrack;
        /*
        // limit heading to -Pi <= heading < Pi
        if (m_currentPose.theta > M_PI)
            m_currentPose.theta -= 2 * M_PI;
        else if (m_currentPose.theta <= -M_PI)
            m_currentPose.theta += 2 * M_PI;
       */ 
        m_currentPose.x = deltaDistanceTravelled()* sin(m_currentPose.theta) + m_previousPose.x;
        m_currentPose.y = deltaDistanceTravelled()* cos(m_currentPose.theta) + m_previousPose.y;

        m_previousPose = m_currentPose;
        return m_currentPose;
    }
    
    void Steer::goToAngle(float targetHeading){
        int gain = 0.5 ;
        float error = targetHeading - getPose().theta;

        if (error > M_PI)
            error -= 2 * M_PI;
        else if (error < -M_PI)
            error += 2 * M_PI;

        //Proportional controller
        int controlSpeed = MAX_POWER - (int)(0.5 * m_abs(error)/MAX_ERROR  * MAX_POWER);
        
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
 
    /*
    Pose Steer::getPose(){
        
        m_previousPose = m_currentPose;
        float distance = (m_previousDistanceL - m_previousDistanceR)/2;
        
        m_currentPose.theta = m_previousPose.theta + (m_previousDistanceL - m_previousDistanceR)/m_axleTrack;
        m_currentPose.x = distance * sin(m_currentPose.theta) + m_previousPose.x;
        m_currentPose.y = distance * cos(m_currentPose.theta) + m_previousPose.y;
        
        m_previousDistanceL = m_rightWheel.distance();
        m_previousDistanceR = m_rightWheel.distance();        
        
        return m_currentPose;
    }
    */
//namespace Steering
};
