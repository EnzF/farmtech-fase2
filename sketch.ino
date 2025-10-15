#include <DHT.h>

// --- Pinos (ajuste se seu diagrama usar outros) ---
#define BTN_N     12
#define BTN_P     13
#define BTN_K     14
#define LDR_PIN   34          // ADC
#define RELAY     26

#define DHTPIN    15          // <- CONFIRA NO SEU DIAGRAMA
#define DHTTYPE   DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(BTN_N, INPUT_PULLUP);
  pinMode(BTN_P, INPUT_PULLUP);
  pinMode(BTN_K, INPUT_PULLUP);

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);   // começa desligado
}

void loop() {
  // --- Leituras dos sensores ---
  float umidade = dht.readHumidity();
  float temp     = dht.readTemperature();

  int ldrValue   = analogRead(LDR_PIN);              // 0..4095
  float ph       = (ldrValue / 4095.0) * 14.0;       // escala 0..14

  // Botões com PULLUP: pressionado = LOW -> usamos "!"
  bool N = !digitalRead(BTN_N);
  bool P = !digitalRead(BTN_P);
  bool K = !digitalRead(BTN_K);

  // Trata leituras inválidas do DHT
  if (isnan(umidade) || isnan(temp)) {
    Serial.println("Falha ao ler DHT22. Tentando novamente...");
    delay(1000);
    return;
  }

  // --- Log no Serial ---
  Serial.print("Umidade: "); Serial.print(umidade, 1);
  Serial.print("% | Temp: "); Serial.print(temp, 1);
  Serial.print("C | pH: ");   Serial.print(ph, 2);
  Serial.print(" | NPK: ");   Serial.print(N); Serial.print(P); Serial.print(K);
  Serial.println();

  // --- Regra de irrigação (exemplo: cana) ---
  if (umidade < 40 && ( N || P || K) && ph >= 6.0 && ph <= 7.5) {
    digitalWrite(RELAY, HIGH);
    Serial.println("💧 Irrigacao LIGADA");
  } else {
    digitalWrite(RELAY, LOW);
    Serial.println("🌿 Irrigacao DESLIGADA");
  }

  delay(500);
}
