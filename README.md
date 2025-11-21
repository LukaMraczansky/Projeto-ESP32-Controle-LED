# Projeto: Controle de LED com ESP32 via Servidor Web (Simulação Wokwi)

Este projeto demonstra o funcionamento de um **servidor web utilizando um ESP32** para controlar um LED através de uma página HTML simples.  
O desenvolvimento foi realizado integralmente no **Wokwi**, que permite simular o comportamento do microcontrolador e seus periféricos.

---

## 📌 Objetivo

Criar um sistema no qual o usuário possa **ligar ou desligar um LED** utilizando botões exibidos em uma página web hospedada no próprio ESP32.

Como o Wokwi não cria redes Wi-Fi reais, o acesso ao servidor ocorre através de uma **interface simulada** gerada pelo próprio emulador.

---

## 🧩 Funcionamento do Projeto

1. O ESP32 cria um ponto de acesso Wi-Fi (simulado).
2. Um servidor web é iniciado na porta 80.
3. A página principal contém dois botões:
   - **LIGAR**
   - **DESLIGAR**
4. Cada botão aciona uma rota (endpoint):
   - `/on` → acende o LED  
   - `/off` → apaga o LED
5. O comportamento do LED é mostrado no simulador Wokwi.

---

## 🖼️ Captura de Tela da Simulação

A imagem abaixo mostra o projeto em funcionamento no Wokwi:

![Simulação do projeto](assets/simulacao.png)

> 📌 *Lembre-se de colocar a imagem dentro da pasta `assets` com o nome `simulacao.png`.*

---

## 🔧 Código Utilizado (`sketch.ino`)

```cpp
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

  digitalWrite(ledPin, HIGH); // LED começa aceso

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
