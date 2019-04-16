#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

ESP8266WebServer server(80); //server
const char* hostAP = "E3BOT"; // WIFI name


//define servo objects
Servo servoG;//servo left wheel
Servo servoD; //servo right wheel
Servo servoTG; //servo left head
Servo servoTD; //servo right head

//define pins
const int pin_servoG = D2; // pin servo left wheel
const int pin_servoD = D3; // pin servo right wheel
const int pin_servoTG = D7; // pin servo left head
const int pin_servoTD = D8; // pin servo right head

int ledblue = D4; //Pin LED BLUE
int ledgreen = D5;//Pin LED Green
int ledred = D6; //Pin LED RED


void setup() {
// define pin mode output or input
  pinMode(ledred,OUTPUT);
  pinMode(ledgreen,OUTPUT);
  pinMode(ledblue,OUTPUT);
   
  //Initialise WIFI
  WiFi.mode(WIFI_AP);
  WiFi.softAP(hostAP, "", 1);
  MDNS.begin(hostAP);
  MDNS.addService("http", "tcp", 80);
  commands();
  server.begin(); 

}

void loop() {
  server.handleClient();
}

void commands() {

           server.on("/on", HTTP_GET, []() {
      digitalWrite(ledred, LOW);
      digitalWrite(ledgreen, LOW);
      digitalWrite(ledblue, LOW);
       server.send(200, "text/json", "light");
  });

         server.on("/blue", HTTP_GET, []() {
      digitalWrite(ledred, HIGH);
      digitalWrite(ledgreen, HIGH);
      digitalWrite(ledblue, LOW);
       server.send(200, "text/json", "blue sea");
  });


         server.on("/green", HTTP_GET, []() {
      digitalWrite(ledblue, HIGH);
        digitalWrite(ledred, HIGH);
      digitalWrite(ledgreen, LOW);
       server.send(200, "text/json", "all green");
  });


         server.on("/red", HTTP_GET, []() {
      digitalWrite(ledgreen, HIGH);
        digitalWrite(ledblue, HIGH);
        digitalWrite(ledred, LOW);
       server.send(200, "text/json", "on fire");
  });


         server.on("/off", HTTP_GET, []() {
      digitalWrite(ledred, HIGH);
      digitalWrite(ledgreen, HIGH);
      digitalWrite(ledblue, HIGH);
       server.send(200, "text/json", "lights off");
  });

server.on("/up", HTTP_GET, []() {
    servoTG.attach(pin_servoTG);
    servoTD.attach(pin_servoTD);

  servoTG.write(0);
  servoTD.write(180);

    server.send(200, "text/json", "UP");
  });

  server.on("/down", HTTP_GET, []() {
    servoTG.attach(pin_servoTG);
   servoTD.attach(pin_servoTD);
   
servoTG.write(180);
servoTD.write(0);
   
    server.send(200, "text/json", "down");
  });

server.on("/forward", HTTP_GET, []() {
    servoG.attach(pin_servoG);
    servoD.attach(pin_servoD);
   
    servoG.write(180);
    servoD.write(0);
    server.send(200, "text/json", "FRONT");
  });


  server.on("/backward", HTTP_GET, []() {
    servoG.attach(pin_servoG);
    servoD.attach(pin_servoD);
    
    servoG.write(0);
    servoD.write(180);
    server.send(200, "text/json", "BACK");
  });

  server.on("/right", HTTP_GET, []() {
    servoG.attach(pin_servoG);
    servoD.attach(pin_servoD);
    
    servoG.write(0);
    servoD.write(0);
    server.send(200, "text/json", "right");
  });
  
  server.on("/left", HTTP_GET, []() {
    servoG.attach(pin_servoG);
    servoD.attach(pin_servoD);
   
    servoG.write(180);
    servoD.write(180);
    server.send(200, "text/json", "left");
  });

  
  
  server.on("/stop", HTTP_GET, []() {
   servoG.detach();
   servoD.detach(); 
   servoTD.detach();
   servoTG.detach();

  server.send(200, "text/json", "");
  });

     
  }
