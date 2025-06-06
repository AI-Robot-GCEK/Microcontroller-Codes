#define WIFI_SSID "jioairfiber"
#define PASSWORD "7559016538"
// For Serial UART 
#define BAUD_RATE 115200
// Not used , 
#define NUM_SERVOS 16
// Remove this in production
#define ENABLE_DEBUG_OUTPUT 1



// MG995 servo specifications:
// - Operating angle: 0° to 180°
// - Pulse width: 500µs to 2500µs
// - PWM Value 102 to 512


#define SERVO_ANGLE_MIN 0
#define SERVO_ANGLE_MAX 180

#define SERVO_MIN  102   // .5ms
#define SERVO_MAX  512   // 2.5ms 
#define SERVO_FREQ 50 // 20ms 

#define CONTROLLER_I2C_ADDR_1 0x41

#define HTTP_SERVER_PORT 80 
#define API_SERVER_PORT 999 

