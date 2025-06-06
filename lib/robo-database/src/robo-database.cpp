// #include "robo-database.h"
// #include "configs.h"

// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <Arduino_JSON.h>
// // 192.168.31.92
// const char* ssid = "jioairfiber";
// const char* password = "7559016538";

// // THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// // For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
// unsigned long lastTime = 0;

// unsigned long timerDelay = 1000;

// String jsonBuffer;

// void setup() {
//   Serial.begin(115200);

//   WiFi.begin(ssid, password);
//   Serial.println("Connecting");
//   while(WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.print("Connected to WiFi network with IP Address: ");
//   Serial.println(WiFi.localIP());
 
//   Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
// }

// void loop() {
//   // Send an HTTP GET request
//   if ((millis() - lastTime) > timerDelay) {
//     // Check WiFi connection status
//     if(WiFi.status()== WL_CONNECTED){
//       String serverPath = "http://192.168.31.92:5000/robots" ;
//       jsonBuffer = httpGETRequest(serverPath.c_str());
//       // Serial.println(jsonBuffer);
//       JSONVar myObject = JSON.parse(jsonBuffer);
  
//       // JSON.typeof(jsonVar) can be used to get the type of the var
//       if (JSON.typeof(myObject) == "undefined") {
//         Serial.println("Parsing input failed!");
//         return;
//       }
    
//       // Serial.print("JSON object = ");
//       // Serial.println(myObject);
//       // Serial.print("Wind Speed: ");
//       Serial.println(myObject[0]["name"]);
//     }
//     else {
//       Serial.println("WiFi Disconnected");
//     }
//     lastTime = millis();
//   }
// }

// String httpGETRequest(const char* serverName) {
//   WiFiClient client;
//   HTTPClient http;
    
//   // Your Domain name with URL path or IP address with path
//   http.begin(client, serverName);
  
//   // Send HTTP GET request
//   int httpResponseCode = http.GET();
  
//   String payload = "{}"; 
  
//   if (httpResponseCode>0) {
//     // Serial.print("HTTP Response code: ");
//     // Serial.println(httpResponseCode);
//     payload = http.getString();
//   }
//   else {
//     Serial.print("Error code: ");
//     Serial.println(httpResponseCode);
//   }
//   // Free resources
//   http.end();

//   return payload;
// }