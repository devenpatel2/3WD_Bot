#include "Steer.h"

namespace Steering{
    Steer::Steer(float axleTrack, const Wheel &leftWheel, const Wheel &rightWheel):
        m_axleTrack(axleTrack), m_leftWheel(leftWheel), m_rightWheel(rightWheel){
    
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

        return (m_leftWheel.distance() + m_rightWheel.distance())/2.0;
        
    }
//namespace Steering
};
