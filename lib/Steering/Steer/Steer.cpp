#include "Steer.h"

namespace Steering{
    Steer::Steer(float axleTrack, const Wheel &leftWheel, const Wheel &rightWheel):
        _axleTrack(axleTrack), _leftWheel(leftWheel), _rightWheel(rightWheel){
    
        }
    
    void Steer::forward(){
        _leftWheel.forward();
        _rightWheel.forward();
    }

    void Steer::forward(float distance){
        float previousDistance = distanceTravelled();
        while(previousDistance + distance > distanceTravelled()){
            forward();
        }
    }

    void Steer::reverse(){
        _leftWheel.reverse();
        _rightWheel.reverse();
    }

    void Steer::reverse(float distance){
        float previousDistance = distanceTravelled();
        while(previousDistance - distance < distanceTravelled()){
            reverse();
        }
    }

    void Steer::stop(){
        _leftWheel.stop();
        _rightWheel.stop();
    }

    float Steer::distanceTravelled(){

        return (_leftWheel.distance() + _rightWheel.distance())/2.0;
        
    }
//namespace Steering
};
