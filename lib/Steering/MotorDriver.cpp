#include "MotorDriver/MotorDriver.h"
#include <Arduino.h>

namespace Steering{
    
    Motor::Motor(MotorSettings motorSettings, EncoderSettings encoderSettings){
        _mtSettings = motorSettings;
        pinMode(_mtSettings.enable, OUTPUT);
        pinMode(_mtSettings.input1, OUTPUT);
        pinMode(_mtSettings.input2, OUTPUT);
        encoder = new Encoder(encoderSettings);
    }
    
    Motor::Motor(MotorSettings motorSettings){
        _mtSettings = motorSettings;
        pinMode(_mtSettings.enable, OUTPUT);
        pinMode(_mtSettings.input1, OUTPUT);
        pinMode(_mtSettings.input2, OUTPUT);
    }
    
    void Motor::forward(){
        if(encoder)
            encoder->setDirection(FORWARD);
        
        digitalWrite(_mtSettings.enable, HIGH);
        digitalWrite(_mtSettings.input1, HIGH);
        digitalWrite(_mtSettings.input2, LOW);
    }

    void Motor::forward(uchar speed){
        if(encoder)
            encoder->setDirection(FORWARD);
        
        analogWrite(_mtSettings.enable, HIGH);
        digitalWrite(_mtSettings.input1, HIGH);
        digitalWrite(_mtSettings.input2, LOW);
    }

    void Motor::reverse(){
        if(encoder)
            encoder->setDirection(REVERSE);

        digitalWrite(_mtSettings.enable, HIGH);
        digitalWrite(_mtSettings.input1, LOW);
        digitalWrite(_mtSettings.input2, HIGH);
    }

    void Motor::reverse(uchar speed){
        if(encoder)
            encoder->setDirection(REVERSE);

        analogWrite(_mtSettings.enable, HIGH);
        digitalWrite(_mtSettings.input1, LOW);
        digitalWrite(_mtSettings.input2, HIGH);
    }
    
    void Motor::stop(){
        digitalWrite(_mtSettings.enable, LOW);
        digitalWrite(_mtSettings.input1, LOW);
        digitalWrite(_mtSettings.input2, LOW);
    }


   Motor::~Motor(){
        delete encoder;
    }
//namespace Steering
};
