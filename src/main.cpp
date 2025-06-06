#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "configs.h"
#include <robo-movements.h>


int servoPositions[16] = {
    LA1_INITIAL_POSITION, LA2_INITIAL_POSITION, LA3_INITIAL_POSITION, RA1_INITIAL_POSITION,
    RA2_INITIAL_POSITION, RA3_INITIAL_POSITION, LH_INITIAL_POSITION, RH_INITIAL_POSITION,
    LL1_INITIAL_POSITION, LL2_INITIAL_POSITION, LL3_INITIAL_POSITION, RL1_INITIAL_POSITION,
    RL2_INITIAL_POSITION, RL3_INITIAL_POSITION, LF_INITIAL_POSITION, RF_INITIAL_POSITION
};


Adafruit_PWMServoDriver board = Adafruit_PWMServoDriver(CONTROLLER_I2C_ADDR_1);


Robo la1(PIN_LA1);
Robo la2(PIN_LA2);
Robo la3(PIN_LA3);
Robo ra1(PIN_RA1);
Robo ra2(PIN_RA2);
Robo ra3(PIN_RA3);
Robo lh(PIN_LH);
Robo rh(PIN_RH);
Robo ll1(PIN_LL1);
Robo ll2(PIN_LL2);
Robo ll3(PIN_LL3);
Robo rl1(PIN_RL1);
Robo rl2(PIN_RL2);
Robo rl3(PIN_RL3);
Robo lf(PIN_LF);
Robo rf(PIN_RF);

// Robo::set_board(board); // Set the board for all Robo objects

Robo* robots[NUM_SERVOS] ={
    &la1, &la2, &la3, &ra1, &ra2, &ra3,
    &lh, &rh, &ll1, &ll2, &ll3, &rl1,
    &rl2, &rl3, &lf, &rf
};
WebServer server(HTTP_SERVER_PORT);

// HTML content for the web interface
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
            fetch(`/setServo?id=${id}&angle=${value}`);
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

void handleRoot() {
    String html = htmlPage;
    char sliderHtml[1000];
    for (int i = 0; i < 16; i++) {
        sprintf(sliderHtml, htmlSliders, i+1, servoPositions[i], i, i, i, servoPositions[i]);
        html += sliderHtml;
    }
    html += "</body></html>";
    server.send(200, "text/html", html);
}

void handleSetServo() {
    if (server.hasArg("id") && server.hasArg("angle")) {
        int id = server.arg("id").toInt();
        int angle = server.arg("angle").toInt();
        
        // Validate parameters
        if (id >= 0 && id < 16 && angle >= SERVO_ANGLE_MIN && angle <= SERVO_ANGLE_MAX) {
            // servoPositions[id] = angle;
            robots[id]->set_angle(angle); // Update the servo position
            String response = "Updated servo " + String(id) + " to position " + String(angle);
            server.send(200, "text/plain", response);
            return;
        }
    }
    server.send(400, "text/plain", "Bad Request - Use: /setServo?id=X&anglee=Y (where X=0-15, Y=0-180)");
}

void setup() {
    Serial.begin(115200);
    // Connect to WiFi
    WiFi.begin(WIFI_SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");
    Serial.println(WiFi.localIP());

    Robo::set_board(board); // Set the board for all Robo objects


    // Initialize all servos to their initial positions
    for (int id = 0; id < 16; id++) {
        if (robots[id] != nullptr) {
            robots[id]->initialize();
            delay(100); 
        } else {
            Serial.println("Error: Robot object for servo " + String(id) + " is null.");
        }
    }
    server.on("/", handleRoot);
    server.on("/setServo", handleSetServo);
    server.begin();
    Serial.print("Web server started -> " ); 
    Serial.println(WiFi.localIP());

}

void loop() {
    server.handleClient(); // Handle client requests
    delay(50);
}
