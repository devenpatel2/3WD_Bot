#pragma once

#include "MotorDriver/MotorDriver.h"
#include "Utils/utils.h"

namespace Steering{
    class Wheel : public Motor{
        public :    
            // for wheel with speed encoder
            Wheel(float radius, MotorSettings motorSettings, EncoderSettings encoderSettings);
            //for wheel without encoder
            Wheel(float radius, MotorSettings motorSettings);
            float distance();

        private :

            float _distancePerRevolution;
    };
// namespace Steering
};
