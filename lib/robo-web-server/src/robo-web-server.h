#ifndef _ROBO_WEB_SERVER_H_
#define _ROBO_WEB_SERVER_H_
#include <WiFi.h>
#include <WebServer.h>
#include <robo.h>
#include "configs.h"
class RoboWebServer {
    public:
        static uint8_t _servoPositions[NUM_SERVOS];
        RoboWebServer(WebServer& server,Robo** roboParts): _server(server), _roboParts(roboParts) {}
        void begin();
        void handleRoot();
        void handleClient();
        void handleSetServobyAngle();
        void handleSetServobyPulse();
    private:
        Robo** _roboParts;
        WebServer& _server;
};
#endif // _ROBO_WEB_SERVER_H_