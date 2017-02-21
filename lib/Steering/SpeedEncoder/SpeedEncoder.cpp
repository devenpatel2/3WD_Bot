#include "SpeedEncoder.h"
#include <Arduino.h>

namespace Steering{

    void Encoder::isr(){
        if ( _rotating ) delay (1);  // wait a little until the bouncing is done

        // Test transition, did things really change? 
        if( digitalRead(_pin) != _isr_set ) {  // debounce once more
            _isr_set = ! _isr_set;

            // adjust counter 
            if ( _isr_set  ) 
                _count = _count + _direction;

            _rotating = false;  // no more debouncing until loop() hits again
        }  
     
    }

    Encoder::Encoder(EncoderSettings encoderSetting){
        _count = 0;
        _lastCount = 1;
        _rotating = false;
        _isr_set = false;    
        _pin = encoderSetting.encoderPin;
        _direction = FORWARD;
        pinMode(_pin, INPUT); 
        // turn on pullup resistors
        digitalWrite(_pin, HIGH);
      
    }

    int Encoder::count(){
        _rotating = true;  // reset the debouncer
            if (_lastCount != _count) {
            _lastCount = _count;
        }
        return (int)_count;
    }

    void Encoder::setDirection(Direction direction){
        _direction = direction;
    }

    Direction Encoder::getDirection(){
        return _direction;
    }

    void Encoder::resetCount(){
        _count = 0;
        _lastCount =1;

    }
//namespace Steering 
};
