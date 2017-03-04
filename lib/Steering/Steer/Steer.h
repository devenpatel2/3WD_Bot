#pragma once
#include "Wheel/Wheel.h"
#include "Utils/utils.h"

namespace Steering{
    class Steer{
        public:
            Steer(float axleTrack, const Wheel &leftWheel, const Wheel &rightWheel);
            void forward();
            void forward(int speed);
            void reverse();
            void reverse(int speed);
            void left(int speed);
            void left();
            void right(int speed);
            void right();
            void stop();
            float distanceTravelled();
            void goToAngle(float targetHeading);
            Pose getPose();
            
        private:
            Wheel m_leftWheel, m_rightWheel;
            float m_axleTrack, m_prevDistanceL, m_previousDistanceR;
            Pose m_previousPose, m_currentPose;
            float m_abs(float value);
            
    };
//namespace Steering
};
