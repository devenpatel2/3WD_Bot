#pragma once
# define M_PI 3.14152 /* pi */
# define MAX_POWER  255
# define MAX_ERROR 2*M_PI
# define MAX_GAIN 10
# define MA_LENGTH 10 //moving average length
typedef unsigned char uchar;

namespace Steering{
    enum Direction{ REVERSE = -1,
                    FORWARD = 1};

    struct MotorSettings{
        uchar enable;
        uchar input1;
        uchar input2;
    };

    struct EncoderSettings{
        uchar encoderPin;
        int countPerRevolution ;
    };

    struct Point{
        float x;
        float y;
    };
    
    struct Pose{
        float x;
        float y;
        float theta;
    };
}

