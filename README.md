# 🌾 FarmTech Solutions — Fase 2 (FIAP)
**Autores:** Enzo França Sader e Larissa  
**Curso:** Tecnologia em Inteligência Artificial (FIAP)  
**Fase 2 – Projeto de IoT: Sistema de Irrigação Inteligente**

---

## 🎯 Objetivo do Projeto
Desenvolver um **sistema de irrigação automatizado** utilizando o microcontrolador **ESP32**, capaz de monitorar a **umidade do solo, níveis de nutrientes (NPK) e pH** da terra, acionando automaticamente uma **bomba d’água (relé)** quando necessário.

O sistema representa uma aplicação real de **IoT e sensoriamento inteligente para o agronegócio**, otimizando o uso de água e recursos agrícolas.

---

## ⚙️ Componentes e Sensores

| Componente | Função | Simulação no Wokwi |
|-------------|--------|--------------------|
| DHT22 | Mede a umidade e temperatura do ar (simulando umidade do solo) | Sensor de umidade |
| LDR | Simula o sensor de pH da terra (0 a 14 convertido a partir da leitura analógica) | Sensor de luz LDR |
| 3 Botões (N, P, K) | Representam os níveis de Nitrogênio, Fósforo e Potássio | Botões verdes |
| Relé | Liga/desliga bomba d’água | Relé azul |
| ESP32 | Microcontrolador principal | Placa base do circuito |

---

## 🧠 Lógica de Funcionamento

1. O DHT22 mede a **umidade** e a **temperatura**.
2. O LDR gera um valor analógico (0–4095) convertido para uma escala de **pH (0 a 14)**.
3. Os três botões simulam os níveis de **N, P, K** (pressionado = nutriente ativo).
4. O sistema ativa a irrigação (`relé HIGH`) **quando:**
   - a umidade é **menor que 40%**;
   - pelo menos um nutriente (N, P ou K) está presente;
   - o **pH está entre 6.0 e 7.5** (faixa ideal para cana-de-açúcar, por exemplo).

---

## 💧 Código ESP32 (C/C++)

```cpp
#include <DHT.h>

#define BTN_N     12
#define BTN_P     13
#define BTN_K     14
#define LDR_PIN   34
#define RELAY     26
#define DHTPIN    15
#define DHTTYPE   DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(BTN_N, INPUT_PULLUP);
  pinMode(BTN_P, INPUT_PULLUP);
  pinMode(BTN_K, INPUT_PULLUP);

  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
}

void loop() {
  float umidade = dht.readHumidity();
  float temp     = dht.readTemperature();

  int ldrValue   = analogRead(LDR_PIN);
  float ph       = (ldrValue / 4095.0) * 14.0;

  bool N = !digitalRead(BTN_N);
  bool P = !digitalRead(BTN_P);
  bool K = !digitalRead(BTN_K);

  if (isnan(umidade) || isnan(temp)) {
    Serial.println("Falha ao ler DHT22. Tentando novamente...");
    delay(1000);
    return;
  }

  Serial.print("Umidade: "); Serial.print(umidade, 1);
  Serial.print("% | Temp: "); Serial.print(temp, 1);
  Serial.print("C | pH: ");   Serial.print(ph, 2);
  Serial.print(" | NPK: ");   Serial.print(N); Serial.print(P); Serial.print(K);
  Serial.println();

  if (umidade < 40 && (N || P || K) && ph >= 6.0 && ph <= 7.5) {
    digitalWrite(RELAY, HIGH);
    Serial.println("💧 Irrigacao LIGADA");
  } else {
    digitalWrite(RELAY, LOW);
    Serial.println("🌿 Irrigacao DESLIGADA");
  }

  delay(500);
}

---
## 📷 Circuito no Wokwi
Adicione aqui o link e a imagem:
- Link: (https://wokwi.com/projects/444837564605766657)
- Imagem: (adicione o print em `wokwi/circuito.png`)

## 📹 Demonstração em vídeo
Link para vídeo no YouTube (não listado): (https://youtu.be/Xn-lF_ZXwkg)

## 👥 Equipe
- **Enzo França Sader**
- **Larissa**

