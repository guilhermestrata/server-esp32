#include <WiFi.h>

const char* ssid = "FIAP-IBM";
const char* password = "Challenge@24!";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Conectando-se à rede Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado! IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Novo cliente conectado");
    
    while (!client.available()) {
      delay(1);
    }

    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    String html = "<html><body><h1>Bem-vindo ao ESP32 de Guilherme Arendt!</h1><p>O endereço IP do ESP32 é: ";
    html += WiFi.localIP().toString();
    html += "</p></body></html>";

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println(html);

    delay(1);
    Serial.println("Cliente desconectado");
  }
}
