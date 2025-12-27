#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "Fire Alarm Project"
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Konfigurasi WiFi
char ssid[] = "master";
char pass[] = "01234567890";

// Pin Sensor & Aktuator
const int sensor_gas  = 34;
const int sensor_api  = 27;
const int relay       = 26;
const int buzzer      = 25;
const int led_merah   = 33;

// Ambang dan Variabel
const int ambangADC = 400;
int sensorGas_ADC;
int sensorApi_Value;
int persenGas;

// Status kontrol & notifikasi
bool manualRelay     = false;
bool kebakaranTerdeteksi = false;
bool sentGasAlert    = false;
bool sentApiAlert    = false;
bool sentFireAlert   = false;

// set up non-blocking blinking
unsigned long previousMillis = 0;
const unsigned long blinkInterval = 300; // interval kedipan
bool ledState = false;
bool buzzerState = false;

// Kontrol manual relay via Blynk
BLYNK_WRITE(V2) {
  int val = param.asInt();
  manualRelay = (val == 1);

  if (!manualRelay) {
    //reset status kebakaran & matikan relay
    kebakaranTerdeteksi = false;
    digitalWrite(relay, LOW);
  } else {
    digitalWrite(relay, HIGH);
  }
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(sensor_gas, INPUT);
  pinMode(sensor_api, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led_merah, OUTPUT);

  digitalWrite(relay, LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(led_merah, LOW);
}

void loop() {
  Blynk.run();

  // Baca sensor gas & flame
  sensorGas_ADC = analogRead(sensor_gas);
  persenGas = map(sensorGas_ADC, 0, 4095, 0, 100);
  sensorApi_Value = !digitalRead(sensor_api);

  // Tentukan status terdeteksi
  bool gasTerdeteksi = (sensorGas_ADC > ambangADC);
  bool apiTerdeteksi = (sensorApi_Value == 1);

  // Kirim ke Blynk
  Blynk.virtualWrite(V0, persenGas);     // Gauge: persentase gas
  Blynk.virtualWrite(V3, gasTerdeteksi); // Status gas (0/1)
  Blynk.virtualWrite(V1, sensorApi_Value); // Status api (0/1)

  // Debug
  Serial.print("ADC Gas: ");
  Serial.print(sensorGas_ADC);
  Serial.print(" | Persen: ");
  Serial.print(persenGas);
  Serial.print("% | Gas: ");
  Serial.print(gasTerdeteksi);
  Serial.print(" | Api: ");
  Serial.println(sensorApi_Value);

  // Notifikasi hanya sekali per kejadian
  if (gasTerdeteksi && apiTerdeteksi && !sentFireAlert) {
    Blynk.logEvent("fire_alert", "Gas & Api terdeteksi!");
    sentFireAlert = true;
    sentGasAlert = true;
    sentApiAlert = true;
  }
  if (!gasTerdeteksi || !apiTerdeteksi) {
    sentFireAlert = false;
  }

  if (gasTerdeteksi && !apiTerdeteksi && !sentGasAlert) {
    Blynk.logEvent("gas_alert", "Gas terdeteksi, silahkan cek dahulu!");
    sentGasAlert = true;
  }
  if (!gasTerdeteksi) {
    sentGasAlert = false;
  }

  if (apiTerdeteksi && !gasTerdeteksi && !sentApiAlert) {
    Blynk.logEvent("flame_alert", "Api terdeteksi, silahkan cek dahulu!");
    sentApiAlert = true;
  }
  if (!apiTerdeteksi) {
    sentApiAlert = false;
  }

  // Logika alarm non-blocking (tanpa delay)
  unsigned long currentMillis = millis();

  // Cek apakah kebakaran terjadi (gas + api)
  if (gasTerdeteksi && apiTerdeteksi) {
    kebakaranTerdeteksi = true; // Kunci status kebakaran
  }

  if (gasTerdeteksi && apiTerdeteksi) {
    // Kebakaran aktif → buzzer nyala, LED kedip cepat, relay ON
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(led_merah, ledState);
    }
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, HIGH);
  }
  else if (gasTerdeteksi && !apiTerdeteksi) {
    // Hanya gas → LED nyala terus, buzzer bunyi pendek
    if (currentMillis - previousMillis >= 2000) {
      previousMillis = currentMillis;
      digitalWrite(buzzer, HIGH);
      delay(300); // pendek
      digitalWrite(buzzer, LOW);
      digitalWrite(led_merah, HIGH);
    }
    if (!manualRelay && !kebakaranTerdeteksi) {
      digitalWrite(relay, LOW);
    }
  }
  else if (!gasTerdeteksi && apiTerdeteksi) {
    // Hanya api → LED & buzzer kedip lambat
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      ledState = !ledState;
      buzzerState = !buzzerState;
      digitalWrite(led_merah, ledState);
      digitalWrite(buzzer, buzzerState);
    }
    if (!manualRelay && !kebakaranTerdeteksi) {
      digitalWrite(relay, LOW);
    }
  }
  else {
    // Tidak ada deteksi gas/api
    if (currentMillis - previousMillis >= 2000) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(led_merah, ledState);
    }

    // Buzzer & LED kembali idle
    digitalWrite(buzzer, LOW);

    // Relay tetap ON jika kebakaran pernah terjadi
    if (!manualRelay && !kebakaranTerdeteksi) {
      digitalWrite(relay, LOW);
    }
  }
}
