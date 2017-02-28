#include "Steer.h"
#include "Wheel.h"
#include <math.h>
namespace Steering{
    Steer::Steer(float axleTrack, const Wheel &leftWheel, const Wheel &rightWheel):
        m_axleTrack(axleTrack), m_leftWheel(leftWheel), m_rightWheel(rightWheel),
        m_previousPose{0.0f, 0.0f, 0.0f}, m_currentPose{0.0f , 0.0f, 0.0f}{
    
        }
    
    void Steer::forward(){
        m_leftWheel.forward();
        m_rightWheel.forward();
    }

    void Steer::forward(float distance){
        float previousDistance = distanceTravelled();
        while(previousDistance + distance > distanceTravelled()){
            forward();
        }
    }

    void Steer::reverse(){
        m_leftWheel.reverse();
        m_rightWheel.reverse();
    }

    void Steer::reverse(float distance){
        float previousDistance = distanceTravelled();
        while(previousDistance - distance < distanceTravelled()){
            reverse();
        }
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

    float Steer::distanceTravelled(){

        return (m_leftWheel.distance() + m_rightWheel.distance())/2;
        
    }

    Pose Steer::getPose(){
        m_previousPose = m_currentPose;
        
        m_currentPose.theta = m_previousPose.theta + (m_rightWheel.distance() - m_leftWheel.distance())/m_axleTrack;
        m_currentPose.x = distanceTravelled()* sin(m_currentPose.theta) + m_previousPose.x;
        m_currentPose.y = distanceTravelled()* cos(m_currentPose.theta) + m_previousPose.y;

        return m_currentPose;
    }
//namespace Steering
};
