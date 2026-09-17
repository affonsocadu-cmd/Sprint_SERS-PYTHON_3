const int PIN_LDR = A0;      // Sensor Solar (LDR)
const int PIN_POT = A1;      // Sensor de Corrente (Potenciômetro)
const int PIN_RELAY = 7;     // Atuador Relé
const int PIN_LED_GREEN = 2; // Sinalização: Carregando
const int PIN_LED_RED = 4;   // Sinalização: Standby / Indisponível

unsigned long lastMsg = 0;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);

  digitalWrite(PIN_RELAY, LOW);
  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_RED, HIGH);

  Serial.println("--- CHARGEGRID SPRINT 3 INICIADO ---");
}

void loop() {
  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;

    int ldrValue = analogRead(PIN_LDR);
    int potValue = analogRead(PIN_POT);

    float solarIrradiance = map(ldrValue, 0, 1023, 0, 100);
    float currentAmperes = map(potValue, 0, 1023, 0, 320) / 10.0;
    float voltage = 220.0;
    float powerWatts = voltage * currentAmperes;

    bool isCharging = false;

    if (solarIrradiance > 20.0) {
      digitalWrite(PIN_RELAY, HIGH);
      digitalWrite(PIN_LED_GREEN, HIGH);
      digitalWrite(PIN_LED_RED, LOW);
      isCharging = true;
    } else {
      digitalWrite(PIN_RELAY, LOW);
      digitalWrite(PIN_LED_GREEN, LOW);
      digitalWrite(PIN_LED_RED, HIGH);
      isCharging = false;
      currentAmperes = 0.0;
      powerWatts = 0.0;
    }

    Serial.print("TELEMETRIA MQTT [chargegrid/sprint3/telemetry]: ");
    Serial.print("{\"station_id\":\"CHARGEGRID_UNO_01\",");
    Serial.print("\"solar_pct\":"); Serial.print(solarIrradiance, 1);
    Serial.print(",\"voltage_v\":"); Serial.print(voltage, 1);
    Serial.print(",\"current_a\":"); Serial.print(currentAmperes, 1);
    Serial.print(",\"power_w\":"); Serial.print(powerWatts, 1);
    Serial.print(",\"status\":\""); Serial.print(isCharging ? "CHARGING" : "STANDBY");
    Serial.println("\"}");
  }
}
