#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32-LED";
const char* password = "12345678";

WebServer server(80);

const int ledPin = 2;

void handleHome() {
  String html = "<html><body style='text-align:center;font-family:Arial'>";
  html += "<h1>Controle do LED</h1>";
  html += "<a href='/on'><button style='padding:20px;font-size:20px;'>LIGAR</button></a><br><br>";
  html += "<a href='/off'><button style='padding:20px;font-size:20px;'>DESLIGAR</button></a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  digitalWrite(ledPin, HIGH);  
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  pinMode(ledPin, OUTPUT);

  // 🔥 LED começa ACESO
  digitalWrite(ledPin, HIGH);

  Serial.begin(115200);

  WiFi.softAP(ssid, password);

  Serial.println("Servidor iniciado!");
  Serial.print("Acesse: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleHome);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
}

void loop() {
  server.handleClient();
}
