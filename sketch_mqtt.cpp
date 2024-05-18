#include <WiFi.h>
#include <EspMQTTClient.h>

// Configurações de rede Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configurações do broker MQTT
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "TESTMACK1165744/Gas";
const char* mqtt_client_name = "mqtt-mack-pub";

// Instância do cliente MQTT
EspMQTTClient client(
  ssid,
  password,
  mqtt_server,
  "",
  "",
  mqtt_client_name,
  mqtt_port
);

void setup() {
  // Inicia a comunicação serial a 9600 bps para receber dados do Arduino
  Serial.begin(9600); 

  // Configurações do cliente MQTT
  client.enableDebuggingMessages(); 
  // Habilita mensagens de debug no monitor serial
  client.enableHTTPWebUpdater(); 
  // Habilita o atualizador web
  client.enableOTA(); 
  // Habilita atualizações OTA (Over The Air)
}

void onConnectionEstablished() {
  // Publica uma mensagem inicial quando a conexão é estabelecida
  client.publish(mqtt_topic, "Conexão estabelecida com o broker MQTT");
  client.publish(mqtt_topic, "650");
}

void loop() {
  client.loop(); // Necessário para manter a conexão com o broker MQTT ativa

  // Verifica se há dados disponíveis na comunicação serial
  if (Serial.available() > 0) {
    String sensorValue = Serial.readStringUntil('\n'); // Lê os dados enviados pelo Arduino
    sensorValue.trim(); // Remove espaços em branco extras

    // Publica o valor do sensor de gás no tópico MQTT
    client.publish(mqtt_topic, sensorValue);
  }

  delay(1000); // Aguarda 1 segundo antes de verificar novamente
}
