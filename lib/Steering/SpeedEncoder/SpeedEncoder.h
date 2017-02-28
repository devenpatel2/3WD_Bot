#pragma once

#include "Utils/utils.h"
namespace Steering{
    class Encoder{

        public:

            Encoder(const EncoderSettings encoderSettings);
            int count();
            void setDirection(Direction);
            Direction getDirection();
            void setDirection();
            void resetCount();
            void isr();

        private:

            uchar m_pin ;
            volatile int m_count;
            int m_lastCount;
            volatile Direction m_direction;
            bool m_rotating;
            bool m_isr_set;
        
    };
// namespace Steering
};
