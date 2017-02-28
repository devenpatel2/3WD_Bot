#include "MotorDriver.h"
#include <Arduino.h>

namespace Steering{
    
    Motor::Motor(const MotorSettings motorSettings, const EncoderSettings encoderSettings)
    :m_mtSettings(motorSettings), encoder(new Encoder(encoderSettings)){
        pinMode(m_mtSettings.enable, OUTPUT);
        pinMode(m_mtSettings.input1, OUTPUT);
        pinMode(m_mtSettings.input2, OUTPUT);
    }
    
    Motor::Motor(const MotorSettings motorSettings)
    :m_mtSettings(motorSettings){
        pinMode(m_mtSettings.enable, OUTPUT);
        pinMode(m_mtSettings.input1, OUTPUT);
        pinMode(m_mtSettings.input2, OUTPUT);
    }
    
    void Motor::forward(){
        if(encoder)
            encoder->setDirection(FORWARD);
        
        digitalWrite(m_mtSettings.enable, HIGH);
        digitalWrite(m_mtSettings.input1, HIGH);
        digitalWrite(m_mtSettings.input2, LOW);
    }

    void Motor::forward(uchar speed){
        if(encoder)
            encoder->setDirection(FORWARD);
        
        analogWrite(m_mtSettings.enable, speed);
        digitalWrite(m_mtSettings.input1, HIGH);
        digitalWrite(m_mtSettings.input2, LOW);
    }

    void Motor::reverse(){
        if(encoder)
            encoder->setDirection(REVERSE);

        digitalWrite(m_mtSettings.enable, HIGH);
        digitalWrite(m_mtSettings.input1, LOW);
        digitalWrite(m_mtSettings.input2, HIGH);
    }

    void Motor::reverse(uchar speed){
        if(encoder)
            encoder->setDirection(REVERSE);

        analogWrite(m_mtSettings.enable, speed);
        digitalWrite(m_mtSettings.input1, LOW);
        digitalWrite(m_mtSettings.input2, HIGH);
    }
    
    void Motor::stop(){
        digitalWrite(m_mtSettings.enable, LOW);
        digitalWrite(m_mtSettings.input1, LOW);
        digitalWrite(m_mtSettings.input2, LOW);
    }


   Motor::~Motor(){
        delete encoder;
    }
//namespace Steering
};
