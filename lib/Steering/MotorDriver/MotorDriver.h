#pragma once
#include "SpeedEncoder/SpeedEncoder.h"
#include "Utils/utils.h"
namespace Steering{
    class Motor{

        public:
            //for motor with encoder
            Motor(const MotorSettings motorSettings, const EncoderSettings encoderSettings);
            // for motor without encoder
            Motor(const MotorSettings motorSettings);
            ~Motor();
            void forward();
            void forward(uchar speed);
            void reverse();
            void reverse(uchar speed);
            void stop();
            Encoder *encoder;

        private:

            MotorSettings _mtSettings;
            EncoderSettings _enSettings;
    };
//namespace Steering
};
