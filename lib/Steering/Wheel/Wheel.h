#pragma once

#include "MotorDriver/MotorDriver.h"
#include "Utils/utils.h"

namespace Steering{
    class Wheel : public Motor{
        public :    
            Wheel(float radius, MotorSettings motorSettings, EncoderSettings encoderSettings);
            Wheel(float radius, MotorSettings motorSettings);
            float distance();

        private :

            float _distancePerRevolution;
    };
// namespace Steering
};
