int LED = A1;
int MQ2pin = A0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600); // Inicia a comunicação serial a 9600 bps
}

void loop() {
  int sensorValue = analogRead(MQ2pin);
  if (sensorValue >= 300) {
    digitalWrite(LED, LOW);
    // Envia o valor lido do sensor via Serial
    Serial.println(sensorValue);
  } else {
    digitalWrite(LED, HIGH);
  }
  delay(1000);
}