#pragma once
#include "Wheel/Wheel.h"

namespace Steering{
    class Steer{
        public:
            Steer(float axleTrack, const Wheel &wheelLeft, const Wheel &wheelRight);
            void forward();
            void forward(float distance);
            void reverse();
            void reverse(float distance);
            void left();
            void left(float angle);
            void right();
            void right(float angle);
            void stop();
            float distanceTravelled();
            float angle();
        
        private:
            Wheel m_leftWheel, m_rightWheel;
            float m_axleTrack;
    };
//namespace Steering
};
