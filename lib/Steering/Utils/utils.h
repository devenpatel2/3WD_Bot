#pragma once

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
}
