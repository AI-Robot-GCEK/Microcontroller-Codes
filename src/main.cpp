#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <robo-database.h>
#include <robo.h>
// #include <robo-web-server.h>
#include <Adafruit_PWMServoDriver.h>
#include <Arduino_JSON.h>
#include "configs.h"
#include "pins.h"



String httpGETRequest(const char* serverName) {
    WiFiClient client;
    HTTPClient http;
      
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);
    
    // Send HTTP GET request
    int httpResponseCode = http.GET();
    
    String payload = "{}"; 
    
    if (httpResponseCode>0) {
      // Serial.print("HTTP Response code: ");
      // Serial.println(httpResponseCode);
      payload = http.getString();
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  
    return payload;
  }

  
// Create PWM board object
#if !defined(CONTROLLER_I2C_ADDR_2) 
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(CONTROLLER_I2C_ADDR_1);      
Robo la1(PIN_LA1, board1);
Robo la2(PIN_LA2, board1);
Robo la3(PIN_LA3, board1);
Robo ra1(PIN_RA1, board1);
Robo ra2(PIN_RA2, board1);
Robo ra3(PIN_RA3, board1);
Robo lh(PIN_LH, board1);
Robo rh(PIN_RH, board1);
Robo ll1(PIN_LL1, board1);
Robo ll2(PIN_LL2, board1);
Robo ll3(PIN_LL3, board1);
Robo rl1(PIN_RL1, board1);
Robo rl2(PIN_RL2, board1);
Robo rl3(PIN_RL3, board1);
Robo lf(PIN_LF, board1);
Robo rf(PIN_RF, board1);
#endif
#if defined(CONTROLLER_I2C_ADDR_2)
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(CONTROLLER_I2C_ADDR_1);   
Adafruit_PWMServoDriver board2 = Adafruit_PWMServoDriver(CONTROLLER_I2C_ADDR_2);      

Robo la1(PIN_LA1, board1);
Robo la2(PIN_LA2, board1);
Robo la3(PIN_LA3, board1);
Robo ra1(PIN_RA1, board1);
Robo ra2(PIN_RA2, board1);
Robo ra3(PIN_RA3, board1);
Robo lh(PIN_LH, board1);
Robo rh(PIN_RH, board1);
Robo ll1(PIN_LL1, board2,true);
Robo ll2(PIN_LL2, board2,true);
Robo ll3(PIN_LL3, board2,true);
Robo rl1(PIN_RL1, board2,true);
Robo rl2(PIN_RL2, board2,true);
Robo rl3(PIN_RL3, board2,true);
Robo lf(PIN_LF, board2,true);
Robo rf(PIN_RF, board2,true);
#endif

// WebServer web_server_service(SERVER_PORT);

// RoboWebServer robo_server(web_server_service, roboParts);


void setup() {
    Serial.begin(BAUD_RATE);    
    // WiFi.begin(SSID, PASSWORD);
    Robo* roboParts[Robo::get_total_num_servos()] = {
        &la1, &la2, &la3,
        &ra1, &ra2, &ra3,
        &lh,  &rh,
        &ll1, &ll2, &ll3,
        &rl1, &rl2, &rl3,
        &lf,  &rf
    };
    for(uint8_t id=0;id < NUM_SERVOS;id++){
        roboParts[id]->begin();  
        Serial.print("ID: ");
        Serial.println(id);
        delay(50);
    }
    // while (WiFi.status() != WL_CONNECTED) {
    //     delay(1000);
    //     Serial.print(".");
    // }
    // Serial.println("\nConnected to WiFi");
    // Serial.println(WiFi.localIP());

    

    #if ENABLE_DEBUG_OUTPUT
    Serial.println("All Robo parts initialized");
    #endif 

    // Initialize all servos to their initial positions
    // for (int i = 0; i <= NUM_SERVOS; i++) {  // Update loop to use NUM_SERVOS
    //     board1.setPWM(i, 0, roboParts[i]->get_current_pulse());  // Use get_current_pulse for initialization
    // }
    // robo_server.begin(); // Start the web server
}
String httpGETRequest(const char* serverName) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, serverName);
    int httpResponseCode = http.GET();

    String payload = "{}"; // Default empty JSON object
    if (httpResponseCode > 0) {
        payload = http.getString();
    } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
    return payload;
}
void loop() {

    Database db("http://your-database-url");
    if (db.get_data()) {
        Serial.println("Data fetched successfully.");
    } else {
        Serial.println("Failed to fetch data.");
    }
    
    
    // web_server_service.handleClient(); // Handle client requests
    delay(1000); // Delay to avoid flooding the serial output
    for(int i =0 ; i < 1000; i++){
        Serial.print("Hello World ");
        Serial.println(Robo::get_total_num_servos());
        // Serial.println(i);
        delay(1000); // Delay to avoid flooding the serial output           
    }   
    
}
