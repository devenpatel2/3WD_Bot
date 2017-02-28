#include "Wheel.h"

namespace Steering{
    Wheel::Wheel(float radius, MotorSettings motorSettings, EncoderSettings encoderSettings)
        :Motor(motorSettings, encoderSettings){
        
            m_distancePerRevolution = (2* M_PI * radius)/encoderSettings.countPerRevolution;
        }

    Wheel::Wheel(float radius, MotorSettings motorSettings):Motor(motorSettings ){
        
            m_distancePerRevolution = 0; 
        }

    float Wheel::distance(){
        if(encoder) 
            return encoder->count() * m_distancePerRevolution;
        return 0;
    }
//namespace Steering
};
