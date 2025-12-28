# Sistem IoT untuk Deteksi Dini Kebakaran Rumah dengan Sensor Gas dan Api yang Terhubung ke Layanan Pemadam Kebakaran
Nama : Muhammad Ricky Rizaldi    
NIM : 2206030029    

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
10. **Aplikasi Blynk:** Untuk konektivitas dan notifikasi berbasis IoT.

> *) Catatan: Selain perangkat keras, pastikan juga menginstal dependensi yang dibutuhkan

### Langkah-Langkah Instalasi Library & Board:
1. **Instal Board ESP32 di Arduino IDE:**  
   - Buka Arduino IDE → File → Preferences
   - Pada kolom Additional Board Manager URLs, tambahkan:   
     ``` https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json ```
   - Kemudian buka Tools → Board → Boards Manager, cari ESP32 dan klik Install.
   - Saat akan upload pilih board DOIT ESP32 DEVKIT V1
2. **Instal Library Blynk:**   
   - Buka Sketch → Include Library → Manage Libraries
   - Cari Blynk dan pilih Blynk by Volodymyr Shymanskyy
   - Klik Install

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

### 2. Konfigurasi Aplikasi Blynk
Agar sistem alarm kebakaran berbasis ESP32 dapat terhubung dengan aplikasi Blynk dan mengirimkan data secara real-time serta menerima kontrol, ikuti tahapan berikut:
##### 1. Membuat Template dan Device di Blynk  
- Buka [Blynk Console](https://blynk.cloud/dashboard).
- Klik menu “Templates” → **+ New Template**.
- Isi nama: misalnya `Fire Alarm Project`.
- Pilih perangkat: **ESP32**.
- Connection type: **WiFi**.
- Klik **Done**.
- Buka tab “Datastreams” untuk menambahkan virtual pin:

   | Nama        | Tipe    | Pin | Additional        |
   | ----------- | ------- | --- | ----------------- |
   | PersenGas   | Integer | V0  | Range: 0–100      |
   | StatusApi   | Integer | V1  | 0 = aman, 1 = api |
   | ManualRelay | Integer | V2  | 0/1 (write)       |
   | StatusGas   | Integer | V3  | 0 = aman, 1 = gas |

- Simpan, lalu kembali ke **Devices** → klik **+ New Device** → pilih **From Template**, pilih template tadi, lalu beri nama `Fire Alarm`.
- Setelah device dibuat, akan muncul:
   * BLYNK_TEMPLATE_ID
   * BLYNK_TEMPLATE_NAME
   * BLYNK_AUTH_TOKEN
     Salin dan gunakan data ini di kode program.

##### 2. Setup Aplikasi Blynk di HP
- Unduh aplikasi Blynk IoT dari Play Store / App Store.
- Login dengan akun yang sama seperti di Blynk Console.
- Masuk ke menu "Devices", pilih device `Fire Alarm`.
- Klik ikon pensil (edit layout), tambahkan widget berikut:
   * **Gauge** → untuk gas:
     * Datastream: V0 (PersenGas)
     * Label: Persen Gas (%)
   * **LED Widget** → untuk indikator api (V1) dan gas (V3)
   * **Switch** → untuk kontrol manual relay:
     * Datastream: V2
     * Label: Kontrol Relay
     * Mode: Switch (0 = OFF, 1 = ON)
- Simpan dan kembali ke dashboard aplikasi.

##### 3. Menambahkan Notifikasi Otomatis (Event Notification)
- Di Blynk Console → buka template → tab “Events”.
- Buat 3 event baru:

   | Nama Event  | Event Code    | Message                                  |
   | ----------- | ------------- | ---------------------------------------- |
   | Deteksi Gas | `gas_alert`   | Gas terdeteksi, silahkan cek dahulu!     |
   | Deteksi Api | `flame_alert` | Api terdeteksi, silahkan cek dahulu!     |
   | Kebakaran   | `fire_alert`  | Gas & Api terdeteksi! Kebakaran mungkin! |

- Setiap event aktif akan dikirim ke HP pengguna secara otomatis saat dipicu melalui fungsi program

##### 4. Uji Coba dan Verifikasi
Setelah setup selesai:
* Upload kode ke ESP32 versi IoT.
* Buka aplikasi Blynk, nyalakan perangkat.
* Uji sensor menggunakan api / gas.
* Perhatikan:
  * Gauge (V0) naik jika gas terdeteksi.
  * LED indikator menyala sesuai kondisi gas/api.
  * Notifikasi muncul sesuai event.
  * Switch dapat mengontrol relay (ON/OFF).

> Dengan pengaturan ini, sistem alarm sudah sepenuhnya terintegrasi dengan aplikasi Blynk, siap menerima data sensor dan mengirimkan notifikasi secara otomatis.

### 3. Implementasi Kode Sistem Alarm
1. **Versi Konvensional**   
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

2. **Versi IoT**     
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

Berikut adalah isi lengkap untuk dua bagian akhir dalam laporanmu: Bab V (Hasil dan Pembahasan) dan Bab VI (Penutup). Lokasi penempatan gambar juga disertakan sebagai panduan.

---

## HASIL DAN PEMBAHASAN

Setelah seluruh rangkaian disusun dan perangkat diprogram, sistem alarm kebakaran diuji dengan berbagai skenario untuk mengamati respons output terhadap kondisi sensor serta integrasi IoT melalui platform Blynk. Berikut adalah hasil pengamatan dan pembahasan untuk tiap fungsionalitas utama.

### 1. Tampilan Alat

Gambar berikut menunjukkan prototipe alat deteksi dini kebakaran berbasis ESP32 yang telah dirakit:

<img src="https://github.com/user-attachments/assets/87b1a274-bc55-4acd-92e8-f263a02c3d5f" style="width: 30%; height: auto;" />
<img src="https://github.com/user-attachments/assets/28fa247d-f65b-4643-af6a-29b5cdae8ea0" style="width: 30%; height: auto;" />
<img src="https://github.com/user-attachments/assets/21532b11-0095-4d71-bd1a-b80e965e3a34" style="width: 30%; height: auto;" />

Komponen seperti sensor gas, sensor api, buzzer, LED merah, dan relay dihubungkan ke board ESP32 via ekstension board. Penyusunan dilakukan agar mudah diakses saat pengujian serta sesuai dengan konfigurasi pin dalam kode program.

### 2. Respons Sensor Gas dan Api

Pengujian dilakukan dengan mendekatkan sumber asap/gas (misalnya korek gas) ke sensor MQ-135 dan sumber nyala api ke flame sensor. Terlihat bahwa:

* Sensor gas mendeteksi adanya peningkatan konsentrasi gas (nilai ADC > 400).
* Sensor api memberikan logika HIGH (dibalik secara digitalRead menjadi 1) saat menangkap nyala api.

Respons kedua sensor ini langsung tercermin pada Serial Monitor dan indikator LED/buzzer. Hal ini menunjukkan bahwa kalibrasi threshold sudah cukup sensitif untuk mendeteksi kondisi tidak normal secara dini.

### 3. Respons Output Lokal (LED, Buzzer, Relay)
Sistem menunjukkan output berbeda tergantung kombinasi kondisi sensor:
* Saat hanya gas terdeteksi: LED menyala konstan, buzzer bunyi pendek tiap beberapa detik.
* Saat hanya api terdeteksi: LED dan buzzer berkedip lambat.
* Saat gas dan api terdeteksi bersamaan: LED berkedip cepat, buzzer menyala kontinu, dan relay aktif.

Setiap pola diatur dengan teknik non-blocking berbasis millis(), memastikan sistem tetap responsif tanpa menggunakan delay yang dapat menghambat fungsi lainnya.

<img src="https://github.com/user-attachments/assets/62a69021-2761-4ccc-bd1f-69b81dc1e874" style="width: 40%; height: auto;" />
<img src="https://github.com/user-attachments/assets/62a69021-2761-4ccc-bd1f-69b81dc1e874" style="width: 40%; height: auto;" />

### 4. Integrasi Aplikasi Blynk
Setelah konfigurasi template, datastream, dan widget selesai, ESP32 berhasil mengirimkan data real-time ke aplikasi Blynk. Fitur yang diuji meliputi:
* Gauge (V0) menunjukkan persentase gas.
* LED virtual (V1 & V3) menampilkan status api/gas.
* Switch (V2) dapat mengontrol relay secara manual.
* Notifikasi otomatis muncul di HP saat ada deteksi gas, api, atau kebakaran.

<img src="https://github.com/user-attachments/assets/dbb70659-308e-4ce6-a793-744661eaf465" style="width: 50%; height: auto;" />
<img src="https://github.com/user-attachments/assets/43e954df-9381-4db9-9a6a-3ba573b6e27e" style="width: 50%; height: auto;" />
<img src="https://github.com/user-attachments/assets/d4440b24-fe27-4248-a178-16fffb3ff816" style="width: 50%; height: auto;" />
<img src="https://github.com/user-attachments/assets/699f72f3-54cb-4c2a-92d8-31c6c47579be" style="width: 50%; height: auto;" />
<img src="https://github.com/user-attachments/assets/a0ce24cf-9e49-4856-bb2d-5d2298a695e3" style="width: 50%; height: auto;" />
    
Dengan fitur ini, pengguna tidak hanya dapat memantau kondisi rumah dari jarak jauh, tetapi juga menerima peringatan langsung secara real-time. Relay dapat dinyalakan dari aplikasi untuk menyalakan alarm tambahan atau sistem pemadam.

#### 5. Reset Kondisi Relay
Salah satu kelebihan dari sistem ini adalah penggunaan status "terkunci" pada relay jika pernah terjadi kebakaran. Relay akan tetap aktif meskipun sensor kembali normal. Pengguna hanya dapat mematikan relay secara manual melalui tombol di Blynk. Hal ini mencegah potensi sistem kembali ke kondisi aman secara otomatis tanpa intervensi pengguna.

<img src="https://github.com/user-attachments/assets/fd92d73b-334a-49c6-9f35-cf430681dc46" style="width: 30%; height: auto;" />
<img src="https://github.com/user-attachments/assets/7bf29b37-d476-4470-9e74-96934b2c5200" style="width: 30%; height: auto;" />

---

## PENUTUP
### Kesimpulan
Berdasarkan hasil pengujian dan analisis sistem yang telah dikembangkan, dapat diambil beberapa kesimpulan sebagai berikut:
1. Sistem berhasil mengintegrasikan sensor gas dan api dengan mikrokontroler ESP32 untuk mendeteksi potensi kebakaran secara lokal.
2. Pola aktivasi buzzer, LED, dan relay dapat merepresentasikan kondisi bahaya berdasarkan kombinasi status sensor, serta ditangani dengan teknik non-blocking.
3. Integrasi dengan Blynk memungkinkan pemantauan jarak jauh secara real-time serta pengiriman notifikasi otomatis ke perangkat pengguna saat terjadi bahaya.
4. Kontrol manual terhadap relay melalui aplikasi memperkuat fleksibilitas sistem dalam merespons situasi darurat atau pasca kebakaran.


