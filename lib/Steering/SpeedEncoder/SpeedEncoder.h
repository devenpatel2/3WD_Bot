#pragma once

#include "Utils/utils.h"
namespace Steering{
    class Encoder{

        public:

            Encoder(EncoderSettings encoderSettings);
            int getCount();
            void setDirection(Direction);
            Direction getDirection();
            void setDirection();
            void resetCount();
            void isr();

        private:

            uchar _pin ;
            volatile int _count;
            int _lastCount;
            Direction _direction;
            bool _rotating;
            bool _isr_set;
        
    };
// namespace Steering
};
