#include "SpeedEncoder.h"
#include <Arduino.h>

namespace Steering{

    void Encoder::isr(){
        if (m_rotating ) delay (1);  // wait a little until the bouncing is done

        // Test transition, did things really change? 
        if( digitalRead(m_pin) != m_isr_set ) {  // debounce once more
           m_isr_set = !m_isr_set;

            // adjust counter 
            if ( m_isr_set  ) 
               m_count = m_count + m_direction;

           m_rotating = false;  // no more debouncing until loop() hits again
        }  
        //Keep count only for deltaTime
    }

    Encoder::Encoder(const EncoderSettings encoderSetting)
    :m_count(0), m_lastCount(1), m_rotating(false), m_isr_set(false), m_pin(encoderSetting.encoderPin),
    m_direction(FORWARD), m_currentTime(millis()), m_previousTime(0), m_deltaTime(100){
        
        pinMode(m_pin, INPUT); 
        // turn on pullup resistors
        digitalWrite(m_pin, HIGH);
      
    }

    int Encoder::count(){
       m_rotating = true;  // reset the debouncer
            if (m_lastCount != m_count) {
           m_lastCount = m_count;
        }
        
        return (int)m_count;
    }

    void Encoder::setDirection(Direction direction){
       m_direction = direction;
    }

    Direction Encoder::getDirection(){
        return m_direction;
    }

    void Encoder::resetCount(){
       m_count = 0;
       m_lastCount =1;

    }
//namespace Steering 
};
