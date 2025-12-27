# Sistem IoT untuk Deteksi Dini Kebakaran Rumah dengan Sensor Gas dan Api yang Terhubung ke Layanan Pemadam Kebakaran

## Latar Belakang

Kebakaran rumah merupakan salah satu jenis bencana yang paling sering terjadi di lingkungan permukiman dan sering kali menimbulkan kerugian material maupun korban jiwa. Banyak kasus kebakaran dipicu oleh kebocoran gas LPG, hubungan arus pendek listrik, atau kelalaian penggunaan api di dalam rumah. Salah satu masalah utama dalam penanganan kebakaran adalah keterlambatan deteksi dan respons, di mana api sudah membesar ketika penghuni atau warga sekitar menyadari adanya kebakaran. Kondisi ini diperburuk ketika tidak ada sistem peringatan dini yang dapat memberikan notifikasi secara cepat dan jelas kepada penghuni maupun pihak terkait.

Perkembangan teknologi sensor dan mikrokontroler membuka peluang untuk membangun sistem deteksi dini kebakaran yang lebih adaptif dan terjangkau. Sensor gas dapat digunakan untuk mendeteksi kebocoran atau peningkatan konsentrasi gas mudah terbakar di udara, sementara sensor api mampu mengenali keberadaan nyala api secara langsung melalui radiasi inframerah. Dengan mengombinasikan kedua jenis sensor ini, sistem dapat memberikan indikasi yang lebih akurat mengenai potensi kebakaran dibanding hanya mengandalkan satu jenis sensor saja.

Berbagai penelitian menunjukkan bahwa penggunaan sensor gas dan api berbasis mikrokontroller efektif untuk deteksi kebakaran di skala ruangan atau rumah. [Hutagalung (2018)](https://journal.istn.ac.id/index.php/rekayasainformasi/article/view/279)  merancang sistem pendeteksi kebocoran gas dan api menggunakan sensor MQ-2 dan flame detector berbasis Arduino Uno untuk aplikasi di perumahan dan perkantoran. [Rahmawati & Aeni (2019)](https://jurnal.uns.ac.id/itsmart/article/view/32376) juga mengembangkan sistem pendeteksi kebakaran berbasis Arduino yang mengombinasikan sensor gas dan api, dengan keluaran berupa alarm suara sebagai peringatan dini. Hasil-hasil tersebut menegaskan bahwa integrasi sensor gas dan api merupakan fondasi yang kuat untuk pengembangan sistem keamanan kebakaran skala rumah. Lebih lanjut, pada beberapa penelitian terkini, sistem serupa mulai dikembangkan ke arah Internet of Things (IoT) dengan memanfaatkan jaringan nirkabel untuk mengirimkan notifikasi ke perangkat pengguna maupun pihak berwenang, seperti yang ditunjukkan pada penelitian [Kurnia _et al._ (2023)](https://www.researchgate.net/publication/375791861_DEVELOPMENT_OF_IoT_SYSTEMS_FOR_FIRE_DETECTION_TOOLS_USING_ESP_8266_AND_TELEGRAM_NOTIFICATIONS).


## Rumusan Masalah

Berdasarkan latar belakang tersebut, rumusan masalah yang diangkat dalam proyek ini adalah sebagai berikut:

1. Bagaimana merancang sistem deteksi dini kebakaran berbasis mikrokontroler yang mampu membaca potensi bahaya melalui sensor gas dan sensor api?
2. Bagaimana merancang pola notifikasi lokal melalui LED, buzzer, dan relay yang mampu merepresentasikan tingkat bahaya berdasarkan kombinasi kondisi gas dan api?
3. Bagaimana mengembangkan sistem IoT yang dapat mengirimkan notifikasi potensi kebakaran secara real-time kepada pengguna dan terhubung dengan layanan pemadam kebakaran?

## Tujuan

Tujuan dari proyek ini adalah:

1. Merancang dan membangun prototipe sistem deteksi dini kebakaran berbasis mikrokontroler ESP32 yang mampu membaca potensi bahaya melalui sensor gas dan sensor api.
2. Mengimplementasikan pola peringatan lokal melalui LED, buzzer, dan relay yang mampu merepresentasikan tingkat bahaya berdasarkan kombinasi kondisi sensor gas dan sensor api.
3. Mengembangkan rancangan awal sistem IoT yang mampu mengirimkan notifikasi potensi kebakaran secara real-time kepada pengguna melalui layanan Blynk dan menyediakan mekanisme koneksi ke layanan pemadam kebakaran.

## Alat dan Bahan

Pada proyek ini, alat dan bahan yang digunakan adalah sebagai berikut:

1. **Mikrokontroler**: ESP32
2. **Sensor Gas**: Sensor gas analog MQ-135 yang mampu mendeteksi gas mudah terbakar ataupun asap.
3. **Sensor Api**: Sensor api digital berbasis inframerah yang memberikan keluaran logika (HIGH/LOW) sesuai keberadaan api.
4. **LED Merah**: Sebagai indikator visual kondisi bahaya atau status sistem.
5. **Buzzer**: Sebagai indikator suara untuk memberikan peringatan audio dengan pola tertentu.
6. **Relay:** Untuk mengontrol beban eksternal seperti pompa air atau alarm tambahan.
7. **Kabel jumper dan breadboard**: Untuk menyusun rangkaian prototipe.
8. **Sumber daya**: Daya dari port USB laptop/PC atau adaptor 5V untuk Arduino.
9. **Laptop/PC**: Untuk memprogram ESP32 menggunakan Arduino IDE dan memonitor keluaran melalui Serial Monitor.
10. Aplikasi Blynk: Untuk konektivitas dan notifikasi berbasis IoT.

> *) komponen disesuaikan hanya untuk kebutuhan proyek ini

## Pengujian Komponen

### 1. Pengujian Sensor

Langkah pertama yang dilakukan adalah menguji sensor gas dan sensor api menggunakan ESP32 untuk memastikan keduanya memberikan respons yang sesuai sebelum diintegrasikan dengan komponen output.

Kode pengujian sensor yang digunakan adalah sebagai berikut (disederhanakan):

```cpp
const int sensor_gas = 34;   // GPIO34 = ADC
const int sensor_api = 27;   // GPIO27 = digital input

int sensorGas_ADC;
int sensorApi_Value;

void setup() {
  Serial.begin(115200);
  pinMode(sensor_gas, INPUT);
  pinMode(sensor_api, INPUT);
}

void loop() {
  sensorGas_ADC = analogRead(sensor_gas);          // nilai ADC gas (0–4095)
  sensorApi_Value = !digitalRead(sensor_api);      // dibalik karena aktif LOW

  Serial.println("Nilai Sensor Gas (ADC): " + String(sensorGas_ADC));
  Serial.println("Nilai Sensor Api (digital): " + String(sensorApi_Value));
  delay(500);
}
```

> Pada tahap ini, fokus utama adalah mengamati nilai pembacaan sensor di Serial Monitor ketika lingkungan dalam kondisi normal dan ketika diberikan stimulus, seperti mendekatkan sumber gas (misalnya uap LPG atau asap pembakaran) ke sensor gas atau nyala api kecil ke sensor api. Berdasarkan pengamatan, ditetapkan nilai ambang (threshold) awal untuk sensor gas, yaitu sensorGas_ADC > 400 dianggap sebagai indikasi adanya peningkatan konsentrasi gas yang berpotensi berbahaya, sedangkan untuk sensor api digunakan logika sensorApi_Value == 1 sebagai indikator adanya api.

### 2. Pengujian Output (LED, Relay dan Buzzer)

Setelah sensor terverifikasi berfungsi, langkah berikutnya adalah menguji komponen output secara mandiri. Tujuannya untuk memastikan LED, buzzer, dan relay dapat dikendalikan oleh ESP32 dengan benar sebelum diterapkan logika alarm kebakaran.

Pengujian dilakukan dengan menyalakan dan mematikan LED, buzzer, dan relay secara berkala menggunakan kode sederhana berikut:

```cpp
const int led_merah = 33;
const int buzzer    = 25;
const int relay     = 26;

void setup() {
  Serial.begin(115200);
  pinMode(led_merah, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);

  digitalWrite(led_merah, LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(relay, LOW);
}

void loop() {
  digitalWrite(led_merah, HIGH);
  digitalWrite(buzzer, HIGH);
  digitalWrite(relay, HIGH);
  Serial.println("LED, Buzzer, Relay: ON");
  delay(500);

  digitalWrite(led_merah, LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(relay, LOW);
  Serial.println("LED, Buzzer, Relay: OFF");
  delay(500);
}
```

> Dari pengujian ini dapat dipastikan bahwa LED menyala dan padam dengan benar, buzzer menghasilkan bunyi beep periodik, dan relay dapat aktif. Tahapan ini penting sebagai dasar sebelum menghubungkan output tersebut dengan kondisi sensor gas dan api.

### 3. Pengujian Konektivitas Wifi
Setelah komponen input dan output berhasil diuji, langkah berikutnya adalah memastikan bahwa modul ESP32 dapat terhubung dengan jaringan WiFi. Hal ini penting sebagai dasar bagi komunikasi Internet of Things (IoT) yang akan digunakan pada sistem ini.

Pengujian dilakukan dengan menggunakan kode berikut:
```
#include <WiFi.h>

const char* ssid = "master";           // Ganti dengan nama WiFi Anda
const char* password = "01234567890";  // Ganti dengan password WiFi Anda

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Menghubungkan ke WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nTerhubung ke WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
}
```
> Jika koneksi berhasil, maka pada Serial Monitor akan muncul pesan Terhubung ke WiFi! disertai dengan alamat IP lokal ESP32. Pengujian ini bertujuan untuk memverifikasi jaringan sebelum melanjutkan ke integrasi layanan Blynk.

### 4. Pengujian Koneksi Blynk
Jika koneksi berhasil, maka pada Serial Monitor akan muncul pesan Terhubung ke WiFi! disertai dengan alamat IP lokal ESP32. Pengujian ini bertujuan untuk memverifikasi jaringan sebelum melanjutkan ke integrasi layanan Blynk.

```
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
```
> Setelah berhasil dijalankan, ESP32 akan menampilkan pesan status koneksi melalui Serial Monitor setiap 2 detik. Jika tidak ada kendala dan tidak muncul error koneksi, maka perangkat berhasil terhubung ke server Blynk. Artinya, ESP32 telah siap untuk mengirimkan data sensor serta notifikasi alarm ke platform Blynk secara real-time.

## Pembuatan Alat

Pada tahap pembuatan alat, sistem mulai mengintegrasikan pembacaan sensor dengan pengendalian LED dan buzzer untuk membentuk sebuah alarm kebakaran sederhana. Fokus utama masih pada versi konvensional (non-IoT), di mana peringatan hanya diberikan secara lokal melalui indikator visual dan audio.

### 1. Desain Logika Sistem

Logika sistem dirancang untuk membedakan beberapa kondisi berdasarkan kombinasi status sensor gas dan sensor api, dengan tujuan merepresentasikan tingkat bahaya yang berbeda. Selain aktivasi LED dan buzzer, sistem ini juga mengaktifkan relay sebagai pengendali perangkat eksternal (water sprinkle) dan menerapkan logika “penguncian” ketika kebakaran terdeteksi. Secara ringkas, aturan logika yang digunakan adalah:

1. **Standby (tidak ada gas dan tidak ada api)**

   * `gasTerdeteksi == false` dan `apiTerdeteksi == false`
   * Buzzer **OFF**.
   * Relay: OFF, kecuali dinyalakan manual via Blynk
   * LED memberikan **pola heartbeat**: nyala singkat setiap beberapa detik sebagai indikator bahwa sistem aktif dan siaga.

2. **Hanya gas terdeteksi**

   * `gasTerdeteksi == true` dan `apiTerdeteksi == false`
   * LED **menyala terus** sebagai tanda adanya potensi bahaya.
   * Buzzer memberikan **beep jarang** (ON sebentar, OFF lebih lama) untuk menunjukkan peringatan tingkat awal terkait kebocoran atau peningkatan gas.
   * Relay: tetap OFF kecuali dikendalikan manual

3. **Hanya api terdeteksi**

   * `gasTerdeteksi == false` dan `apiTerdeteksi == true`
   * LED dan buzzer **blink cepat secara bersamaan**, merepresentasikan kondisi bahaya menengah.
   * Relay: tetap OFF kecuali dikendalikan manual

4. **Gas dan api terdeteksi bersamaan**

   * `gasTerdeteksi == true` dan `apiTerdeteksi == true`
   * Buzzer menyala **non-stop (kontinu)** sebagai alarm maksimum.
   * LED **blink** dengan periode sedang, menegaskan bahwa sistem berada dalam kondisi bahaya tinggi.
   * Relay: AKTIF secara otomatis dan akan tetap menyala (terkunci) sampai dinonaktifkan secara manual via aplikasi Blynk

Desain ini mengadopsi pendekatan hierarkis: semakin tinggi tingkat bahaya, semakin intens pola bunyi dan cahaya. Pendekatan ini bertujuan memudahkan pengguna membedakan tingkat risiko hanya dengan memperhatikan perilaku LED, buzzer, dan relay, bahkan tanpa memerlukan visualisasi data di layar monitor. Penggunaan relay memungkinkan sistem untuk bereaksi lebih aktif terhadap kondisi darurat, seperti menyalakan mekanisme water sprinkle.

### 2. Implementasi Kode Sistem Alarm
1. Versi Konvensional
Berikut adalah potongan kode implementasi sistem alarm kebakaran versi konvensional (tanpa koneksi internet), menggunakan ESP32 sebagai mikrokontroler utama. Kode ini mengintegrasikan pembacaan sensor gas dan api dengan logika aktivasi LED, buzzer, serta relay sebagai output pengendali eksternal.

```cpp
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

bool kebakaranTerdeteksi = false;

// Timer non-blocking
unsigned long previousMillis = 0;
const unsigned long blinkInterval = 300;
bool ledState = false;
bool buzzerState = false;

void setup() {
  Serial.begin(115200);

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
  // Baca sensor
  sensorGas_ADC = analogRead(sensor_gas);
  sensorApi_Value = !digitalRead(sensor_api); // LOW saat api terdeteksi

  bool gasTerdeteksi = sensorGas_ADC > ambangADC;
  bool apiTerdeteksi = (sensorApi_Value == 1);

  // Tampilkan ke Serial Monitor
  Serial.print("ADC Gas: ");
  Serial.print(sensorGas_ADC);
  Serial.print(" | Gas: ");
  Serial.print(gasTerdeteksi);
  Serial.print(" | Api: ");
  Serial.print(sensorApi_Value);
  Serial.print(" | Kebakaran: ");
  Serial.println(kebakaranTerdeteksi);

  // Reset via Serial input
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input.equalsIgnoreCase("reset")) {
      kebakaranTerdeteksi = false;
      digitalWrite(relay, LOW);
      Serial.println(">> Status kebakaran direset, relay dimatikan.");
    }
  }

  // Timer non-blocking
  unsigned long currentMillis = millis();

  // Jika terdeteksi gas dan api bersamaan
  if (gasTerdeteksi && apiTerdeteksi) {
    kebakaranTerdeteksi = true;
  }

  if (gasTerdeteksi && apiTerdeteksi) {
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(led_merah, ledState);
    }
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, HIGH);
  }
  else if (gasTerdeteksi && !apiTerdeteksi) {
    if (currentMillis - previousMillis >= 2000) {
      previousMillis = currentMillis;
      digitalWrite(buzzer, HIGH);
      delay(300);
      digitalWrite(buzzer, LOW);
      digitalWrite(led_merah, HIGH);
    }
    if (!kebakaranTerdeteksi) digitalWrite(relay, LOW);
  }
  else if (!gasTerdeteksi && apiTerdeteksi) {
    if (currentMillis - previousMillis >= 1000) {
      previousMillis = currentMillis;
      ledState = !ledState;
      buzzerState = !buzzerState;
      digitalWrite(led_merah, ledState);
      digitalWrite(buzzer, buzzerState);
    }
    if (!kebakaranTerdeteksi) digitalWrite(relay, LOW);
  }
  else {
    // Idle
    if (currentMillis - previousMillis >= 2000) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(led_merah, ledState);
    }
    digitalWrite(buzzer, LOW);
    if (!kebakaranTerdeteksi) digitalWrite(relay, LOW);
  }
}
```
> Versi ini bersifat standalone, di mana peringatan diberikan secara lokal menggunakan komponen fisik tanpa koneksi internet. telah diuji dan berfungsi.

2. Versi IoT
Versi ini merupakan pengembangan dari sistem alarm konvensional dengan menambahkan konektivitas ke platform Blynk IoT. Dengan integrasi ini, ESP32 tidak hanya berfungsi sebagai unit deteksi lokal, tetapi juga mampu mengirimkan data sensor gas dan api ke aplikasi Blynk secara real-time. Pengguna dapat memantau tingkat konsentrasi gas (dalam bentuk persen), status deteksi api, serta mengakses sistem alarm dari jarak jauh. Blynk juga digunakan untuk menampilkan indikator status dan mengirimkan notifikasi langsung ke perangkat pengguna saat terjadi peningkatan gas, munculnya api, atau keduanya sekaligus. Selain itu, tersedia fitur kontrol manual untuk menyalakan atau mematikan relay melalui tombol di aplikasi.

```
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
```
> Dengan implementasi ini, sistem alarm menjadi lebih informatif dan responsif. Pendekatan non-blocking digunakan untuk mengatur pola kedipan LED dan bunyi buzzer tanpa menghambat proses lainnya. Fitur notifikasi berbasis event juga memastikan pengguna mendapatkan peringatan hanya satu kali per kejadian, sehingga tidak terjadi spam. Selain itu, sistem akan tetap mengaktifkan relay meskipun sensor kembali normal, sebagai indikator bahwa pernah terjadi kondisi bahaya, hingga pengguna meresetnya lewat aplikasi. Hal ini menjadikan versi IoT ini sangat cocok untuk aplikasi pemantauan kebakaran secara real-time di lingkungan rumah maupun industri.
