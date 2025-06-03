#include "robo-web-server.h"
#include "configs.h"
#include <Arduino.h>



uint8_t RoboWebServer::_servoPositions[16] = { 
    LA1_INITIAL_POSITION, LA2_INITIAL_POSITION , LA3_INITIAL_POSITION,
    RA1_INITIAL_POSITION, RA2_INITIAL_POSITION, RA3_INITIAL_POSITION,
    LH_INITIAL_POSITION, RH_INITIAL_POSITION, 
    LL1_INITIAL_POSITION, LL2_INITIAL_POSITION, LL3_INITIAL_POSITION,
    RL1_INITIAL_POSITION, RL2_INITIAL_POSITION, RL3_INITIAL_POSITION,
    LF_INITIAL_POSITION, RF_INITIAL_POSITION
};


const char* htmlPage = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
        <title>Servo Position Control</title>
        <style>
            .slider-container { margin: 10px 0; }
        </style>
        <script>
            function updateServo(id, value) {
                document.getElementById('position' + id).innerText = value;
                fetch(`/setServo?id=${id}&position=${value}`);
            }
        </script>
    </head>
    <body>  
        <h1>Servo Position Control</h1>
)rawliteral";
    
    
const char* htmlSliders = R"rawliteral(
    <div class="slider-container">
        LA%d: <input type="range" min="0" max="180" value="%d" id="slider%d" 
        oninput="updateServo(%d, this.value)">
        <span>Position: <span id="position%d">%d</span></span>
    </div>
)rawliteral";


void RoboWebServer::handleRoot() {
    String html = htmlPage;
    char sliderHtml[1000];
    for (int i = 0; i < 16; i++) {
        sprintf(sliderHtml, htmlSliders, i+1, RoboWebServer::_servoPositions[i], i, i, i, RoboWebServer::_servoPositions[i]);
        html += sliderHtml;
    }
    html += "</body></html>";
    _server.send(200, "text/html", html);
}



// byangle
void RoboWebServer::handleSetServo() {
    if (_server.hasArg("id") && _server.hasArg("angle")) {
        Serial.printf("handleSetServobyAngle");
        uint8_t id = _server.arg("id").toInt();
        uint8_t angle = _server.arg("angle").toInt();
        // Validate parameters
        if (id >= 0 && id < 16 && angle >= SERVO_ANGLE_MIN && angle <= SERVO_ANGLE_MAX) {
            _roboParts[id]->set_angle(angle);  // Fix: Use set_angle instead of set_pulse
            String response = "Updated servo " + String(id) + " to angle " + String(angle);
            _server.send(200, "text/plain", response);
            return;
        }
    }
    _server.send(400, "text/plain", "Bad Request - Use: /setServoAngle?id=X&angle=Y (where X=0-15, Y=0-180)");
}

// void RoboWebServer::handleSetServobyPulse() {
//     if (_server.hasArg("id") && _server.hasArg("pulse")) {
//         uint8_t id = _server.arg("id").toInt();
//         uint16_t pulse = _server.arg("pulse").toInt();
//         // Validate parameters
//         if (id >= 0 && id < 16 && pulse >= SERVO_MIN && pulse <= SERVO_MAX) {
//             _roboParts[id]->set_pulse(pulse);  // Use set_pulse instead of set_angle
//             String response = "Updated servo " + String(id) + " to pulse " + String(pulse);
//             _server.send(200, "text/plain", response);
//             return;
//         }
//     }
//     _server.send(400, "text/plain", "Bad Request - Use: /setServoPulse?id=X&pulse=Y (where X=0-15, Y=102-512)");
// }


void RoboWebServer::begin() {
    _server.on("/", std::bind(&RoboWebServer::handleRoot, this));
    _server.on("/setServo", std::bind(&RoboWebServer::handleSetServo, this));
    // _server.on("/setServoPulse", std::bind(&RoboWebServer::handleSetServobyPulse, this));
    // Add a catch-all handler for undefined routes
    _server.onNotFound([this]() {
        Serial.println("Request handler not found");
        _server.send(404, "text/plain", "404 Not Found");
    });
    _server.begin();
}
