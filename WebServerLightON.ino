#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "AGRONOVO19";
const char* password = "Kintin1+";

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