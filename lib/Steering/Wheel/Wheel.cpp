#include "Wheel.h"

namespace Steering{
    Wheel::Wheel(float radius, MotorSettings motorSettings, EncoderSettings encoderSettings)
        :Motor(motorSettings, encoderSettings){
        
            _distancePerRevolution = (2* M_PI * radius)/encoderSettings.countPerRevolution;
        }

    Wheel::Wheel(float radius, MotorSettings motorSettings):Motor(motorSettings ){
        
            _distancePerRevolution = 0; 
        }

    float Wheel::distance(){
        if(encoder) 
            return encoder->count() * _distancePerRevolution;
        return 0;
    }
//namespace Steering
};
