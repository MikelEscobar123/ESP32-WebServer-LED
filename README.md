# Control de LED con ESP32 y WebServer

## Descripción
Proyecto que permite encender y apagar un LED conectado a un ESP32 desde una página web. 
La página muestra el estado actual del LED y cambia de color según esté encendido o apagado.

## Objetivos
- Conectar el ESP32 a WiFi.
- Crear un servidor web básico.
- Controlar un LED desde el navegador.

## Materiales
- ESP32 DevKit
- LED y resistencia (~270 Ω)
- Cables y protoboard
- Arduino IDE

## Código
"""
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "NOMBRE_WIFI";
const char* password = "CONTRASEÑA_WIFI";

const int ledPin = 23;
bool ledState = false;

WebServer server(80);

// Función para la ruta raíz
void handleRoot() {
  String html = "<h1>Control de LED ESP32</h1>";
  html += "<p>Estado actual del LED: ";
  html += (ledState ? "ENCENDIDO" : "APAGADO");
  html += "</p>";
  html += "<a href=\"/toggle\"><button>Encender/Apagar</button></a>";
  server.send(200, "text/html", html);
}

// Función para cambiar el estado del LED
void handleToggle() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
  server.sendHeader("Location", "/"); // Redirige a la página principal
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WIFI ...");
  }
  Serial.println("Conectado");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);

  server.begin();
  Serial.println("Servidor iniciado");
}

void loop() {
  server.handleClient();
}
"""
