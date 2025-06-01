// This will be the 
#include "robo.h"
#include "pins.h"
#include "configs.h"
#include <Arduino.h>


uint8_t Robo::_total_num_servos = 0;
uint8_t Robo::_current_num_servos = 0;
#if !defined(CONTROLLER_I2C_ADDR_2)
bool Robo::isInitialized  = false; 
#endif
#if defined(CONTROLLER_I2C_ADDR_2)
bool isBoard1Initialized = false ;
bool isBoard2Initialized = false ;
#endif

/*!
* @brief Instantiates new  Robo Part Object.  
*/

Robo::Robo(uint8_t _servo_id,Adafruit_PWMServoDriver& board) : 
    _servo_id(_servo_id), _board(board) {
    _total_num_servos++;
    _current_num_servos++;
    switch(_servo_id){
        case PIN_LA1:
            _initial_angle = LA1_INITIAL_POSITION;
            break;
        case PIN_LA2:
            _initial_angle = LA2_INITIAL_POSITION;
            break;
        case PIN_LA3:
            _initial_angle = LA3_INITIAL_POSITION;
            break;
        case PIN_RA1:
            _initial_angle = RA1_INITIAL_POSITION;
            break;
        case PIN_RA2:
            _initial_angle = RA2_INITIAL_POSITION;
            break;
        case PIN_RA3:
            _initial_angle = RA3_INITIAL_POSITION;
            break;
    #if defined(PIN_LH)
        case PIN_LH:
            _initial_angle = LH_INITIAL_POSITION;
            break;
    #endif
    #if defined(PIN_RH)
        case PIN_RH:
            _initial_angle = RH_INITIAL_POSITION;
            break;
    #endif
    #if defined(PIN_B1)
        case PIN_B1:
            _initial_angle = LH_INITIAL_POSITION;
            break;
    #endif
    #if defined(PIN_B2)
        case PIN_B2:
            _initial_angle = RH_INITIAL_POSITION;
            break;
    #endif
        case PIN_LL1:
            _initial_angle = LL1_INITIAL_POSITION;
            break;
        case PIN_LL2:
            _initial_angle = LL2_INITIAL_POSITION;
            break;
        case PIN_LL3:
            _initial_angle = LL3_INITIAL_POSITION;
            break;
        case PIN_RL1:
            _initial_angle = RL1_INITIAL_POSITION;
            break;
        case PIN_RL2:
            _initial_angle = RL2_INITIAL_POSITION;
            break;
        case PIN_RL3:
            _initial_angle = RL3_INITIAL_POSITION;
            break;
        case PIN_LF:
            _initial_angle = LF_INITIAL_POSITION;
            break;
        case PIN_RF:
            _initial_angle = RF_INITIAL_POSITION;
            break;
        default:
            _initial_angle = 0;
            break;

    }
}
// Robo::~Robo() {
//     _current_num_servos--;
// }

/*!
* @brief Initializes the Robo Part Object.
*/
void Robo::begin(){
    // _total_num_servos = 0 ;
    // _current_num_servos = 0;
#if !defined(CONTROLLER_I2C_ADDR_2)
    if(!Robo::isInitialized){
        Serial.println("Executed Begin ");
        _board.begin();
        _board.setPWMFreq(SERVO_FREQ);
        Robo::isInitialized = true; 

    }
#endif
#if defined(CONTROLLER_I2C_ADDR_2)
if(!Robo::isBoard1Initialized){
    Serial.println("Executed Begin ");
    _board.begin();
    _board.setPWMFreq(SERVO_FREQ);
    Robo::isBoard1Initialized = true; 

}
#endif
    // There is so much to do here , do after flask server finishes 
}
#if defined(CONTROLLER_I2C_ADDR_2)

void Robo::begin(bool isBoard2){
    if(!Robo::isBoard2Initialized){
        Serial.println("Executed Begin ");
        _board.begin();
        _board.setPWMFreq(SERVO_FREQ);
        Robo::isBoard2Initialized = true; 
    
    }
}

#endif

/*!
* @return The total number of servos.
*/
uint8_t Robo::get_total_num_servos(){
    return Robo::_total_num_servos;
}
/*!
* @return The current number of servos.
*/
uint8_t Robo::get_current_num_servos(){
    return _current_num_servos;
}

// /*!
// * @warning used by the PWM Driver 
// * @returns count driver output value  out of 4096
// */
uint16_t Robo::get_pulse(uint8_t _angle){
    // constrain the angle to the min and max values
    _angle = constrain(_angle, SERVO_ANGLE_MIN, SERVO_ANGLE_MAX);
    uint16_t _pulse = map(_angle, SERVO_ANGLE_MIN, SERVO_ANGLE_MAX, SERVO_MIN, SERVO_MAX);
    #ifdef ENABLE_DEBUG_OUTPUT
    Serial.print("Angle: "); Serial.print(_angle);
    Serial.print(" pulse: "); Serial.println(_pulse);
    #endif
    return _pulse;
}


uint8_t Robo::get_current_angle() { 
    return _current_angle; 
}

uint16_t Robo::get_current_pulse() { 
    return get_pulse(_current_angle); 

}


// void Robo::set_angle(uint8_t _angle) {
//     _current_angle = _angle;
//     _board.setPWM(_servo_id, 0, get_pulse(_angle));
// }

// void Robo::set_pulse(uint16_t _pulse) {
//     _previous_angle = _current_angle;
//     _current_angle = map(_pulse, SERVO_MIN, SERVO_MAX, SERVO_ANGLE_MIN, SERVO_ANGLE_MAX);
//     _board.setPWM(_servo_id, 0, _pulse);
// }




