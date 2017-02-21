#pragma once
#include "SpeedEncoder/SpeedEncoder.h"
#include "Utils/utils.h"
namespace Steering{
    class Motor{

        public:
            //for motor with encoder
            Motor(MotorSettings motorSettings, EncoderSettings encoderSettings);
            // for motor without encoder
            Motor(MotorSettings motorSettings);
            ~Motor();
            void forward();
            void forward(uchar speed);
            void reverse();
            void reverse(uchar speed);
            void stop();

        protected:
            Encoder *encoder;

        private:

            MotorSettings _mtSettings;
            EncoderSettings _enSettings;
    };
//namespace Steering
};
