#define BLYNK_TEMPLATE_ID "TMPLxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Tes Koneksi Blynk"
#define BLYNK_AUTH_TOKEN "YourAuthToken"  // Ganti dengan token asli dari Blynk

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "NAMA_WIFI";       // Ganti dengan SSID WiFi
char pass[] = "PASSWORD_WIFI";   // Ganti dengan password WiFi

BlynkTimer timer;

void kirimStatus() {
  Serial.println("Terhubung ke Blynk, sistem berjalan normal...");
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Timer tiap 2 detik untuk print status
  timer.setInterval(2000L, kirimStatus);
}

void loop() {
  Blynk.run();
  timer.run();
}
