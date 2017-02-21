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
            Wheel _leftWheel, _rightWheel;
            float _axleTrack;
    };
//namespace Steering
};
