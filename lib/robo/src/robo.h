#ifndef _ROBO_H_
#define _ROBO_H_
// TODO: add a way to get the current angle from the flask server 

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

// Left Arm 
#define LA1_INITIAL_POSITION 10
#define LA2_INITIAL_POSITION 0
#define LA3_INITIAL_POSITION 16

// Right Arm
#define RA1_INITIAL_POSITION 10
#define RA2_INITIAL_POSITION 0
#define RA3_INITIAL_POSITION 16

// Hips 
#define LH_INITIAL_POSITION 90
#define RH_INITIAL_POSITION 96

// Left Leg 
#define LL1_INITIAL_POSITION 0
#define LL2_INITIAL_POSITION 10
#define LL3_INITIAL_POSITION 141

// Right Leg
#define RL1_INITIAL_POSITION 180
#define RL2_INITIAL_POSITION 170
#define RL3_INITIAL_POSITION 39

// Foots
#define LF_INITIAL_POSITION 99
#define RF_INITIAL_POSITION 99


class Robo{
    public:
        Robo(uint8_t _servo_id,Adafruit_PWMServoDriver& board);
        Robo(uint8_t _servo_id,Adafruit_PWMServoDriver& board,bool isSplitBoard);

        // ~Robo();
        void begin();


        static uint8_t get_total_num_servos();
        static uint8_t get_current_num_servos();
        uint8_t get_current_angle();
        uint16_t get_current_pulse();

        void set_angle(uint8_t _angle);
        // //@brief set the angle of the servo
        void set_pulse(uint16_t _pulse);

        uint16_t get_pulse(uint8_t _angle);

        
    private:
        static uint8_t _total_num_servos;
        static uint8_t _current_num_servos;
        uint8_t _servo_id;
        uint8_t _initial_angle;
        uint8_t _current_angle;
        uint8_t _previous_angle;
        #if !defined(CONTROLLER_I2C_ADDR_2)
        static bool isInitialized ; // Board status 
        #endif 
        #if defined(CONTROLLER_I2C_ADDR_2)
        static bool isBoard1Initialized;
        static bool isBoard2Initialized;
        #endif
        Adafruit_PWMServoDriver _board;
};


#endif // _ROBO_H_

