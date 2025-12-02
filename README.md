# Sistem IoT untuk Deteksi Dini Kebakaran Rumah dengan Sensor Gas dan Api yang Terhubung ke Layanan Pemadam Kebakaran

## Latar Belakang

Kebakaran rumah merupakan salah satu jenis bencana yang paling sering terjadi di lingkungan permukiman dan sering kali menimbulkan kerugian material maupun korban jiwa. Banyak kasus kebakaran dipicu oleh kebocoran gas LPG, hubungan arus pendek listrik, atau kelalaian penggunaan api di dalam rumah. Salah satu masalah utama dalam penanganan kebakaran adalah keterlambatan deteksi dan respons, di mana api sudah membesar ketika penghuni atau warga sekitar menyadari adanya kebakaran. Kondisi ini diperburuk ketika tidak ada sistem peringatan dini yang dapat memberikan notifikasi secara cepat dan jelas kepada penghuni maupun pihak terkait.

Perkembangan teknologi sensor dan mikrokontroler membuka peluang untuk membangun sistem deteksi dini kebakaran yang lebih adaptif dan terjangkau. Sensor gas dapat digunakan untuk mendeteksi kebocoran atau peningkatan konsentrasi gas mudah terbakar di udara, sementara sensor api mampu mengenali keberadaan nyala api secara langsung melalui radiasi inframerah. Dengan mengombinasikan kedua jenis sensor ini, sistem dapat memberikan indikasi yang lebih akurat mengenai potensi kebakaran dibanding hanya mengandalkan satu jenis sensor saja.

Berbagai penelitian menunjukkan bahwa penggunaan sensor gas dan api berbasis Arduino efektif untuk deteksi kebakaran di skala ruangan atau rumah. [Hutagalung (2018)](https://journal.istn.ac.id/index.php/rekayasainformasi/article/view/279)  merancang sistem pendeteksi kebocoran gas dan api menggunakan sensor MQ-2 dan flame detector berbasis Arduino Uno untuk aplikasi di perumahan dan perkantoran. [Rahmawati & Aeni (2019)](https://jurnal.uns.ac.id/itsmart/article/view/32376) juga mengembangkan sistem pendeteksi kebakaran berbasis Arduino yang mengombinasikan sensor gas dan api, dengan keluaran berupa alarm suara sebagai peringatan dini. Hasil-hasil tersebut menegaskan bahwa integrasi sensor gas dan api merupakan fondasi yang kuat untuk pengembangan sistem keamanan kebakaran skala rumah. Lebih lanjut, pada beberapa penelitian terkini, sistem serupa mulai dikembangkan ke arah Internet of Things (IoT) dengan memanfaatkan jaringan nirkabel untuk mengirimkan notifikasi ke perangkat pengguna maupun pihak berwenang, seperti yang ditunjukkan pada penelitian [Kurnia _et al._ (2023)](https://www.researchgate.net/publication/375791861_DEVELOPMENT_OF_IoT_SYSTEMS_FOR_FIRE_DETECTION_TOOLS_USING_ESP_8266_AND_TELEGRAM_NOTIFICATIONS).


## Rumusan Masalah

Berdasarkan latar belakang tersebut, rumusan masalah yang diangkat dalam proyek ini adalah sebagai berikut:

1. Bagaimana merancang sistem deteksi dini kebakaran berbasis mikrokontroler yang mampu membaca potensi bahaya melalui sensor gas dan sensor api?
2. Bagaimana merancang pola notifikasi lokal melalui LED dan buzzer yang mampu merepresentasikan tingkat bahaya berdasarkan kombinasi kondisi gas dan api?
3. Bagaimana mengembangkan sistem IoT yang dapat mengirimkan notifikasi potensi kebakaran secara real-time kepada pengguna dan terhubung dengan layanan pemadam kebakaran?

## Tujuan

Tujuan dari proyek ini adalah:

1. Merancang dan membangun prototipe sistem deteksi dini kebakaran berbasis mikrokontroler yang mampu membaca potensi bahaya melalui sensor gas dan sensor api.
2. Mengimplementasikan pola peringatan lokal melalui LED dan buzzer yang mampu merepresentasikan tingkat bahaya berdasarkan kombinasi kondisi sensor gas dan sensor api.
3. Mengembangkan rancangan awal sistem IoT yang mampu mengirimkan notifikasi potensi kebakaran secara real-time kepada pengguna dan menyediakan mekanisme koneksi ke layanan pemadam kebakaran.

## Alat dan Bahan

Pada proyek ini, alat dan bahan yang digunakan adalah sebagai berikut:

1. **Mikrokontroler**: Arduino Uno
2. **Sensor Gas**: Sensor gas analog MQ-135 yang mampu mendeteksi gas mudah terbakar.
3. **Sensor Api**: Sensor api digital berbasis inframerah yang memberikan keluaran logika (HIGH/LOW) sesuai keberadaan api.
4. **LED Merah**: Sebagai indikator visual kondisi bahaya atau status sistem.
5. **Buzzer**: Sebagai indikator suara untuk memberikan peringatan audio dengan pola tertentu.
6. **Kabel jumper dan breadboard**: Untuk menyusun rangkaian prototipe.
7. **Sumber daya**: Daya dari port USB laptop/PC atau adaptor 5V untuk Arduino.
8. **Laptop/PC**: Untuk memprogram Arduino menggunakan Arduino IDE dan memonitor keluaran melalui Serial Monitor.

> *) komponen akan bertambah seiring tahapan proyek (sejauh ini masih konvensional)

## Pengujian Komponen

### 1. Pengujian Sensor

Langkah pertama yang dilakukan adalah menguji sensor gas dan sensor api secara terpisah untuk memastikan keduanya memberikan respons yang sesuai sebelum diintegrasikan dengan komponen output.

Kode pengujian sensor yang digunakan adalah sebagai berikut (disederhanakan):

```cpp
const int sensor_gas = A0;
const int sensor_api = 3;

float sensorGas_Value;
int sensorApi_Value;

void setup() {
  Serial.begin(9600);
  pinMode(sensor_gas, INPUT);
  pinMode(sensor_api, INPUT);
}

void loop() {
  sensorGas_Value = analogRead(sensor_gas);
  sensorApi_Value = !digitalRead(sensor_api);

  Serial.println("Nilai Sensor Gas: " + String(sensorGas_Value));
  Serial.println("Nilai Sensor Api: " + String(sensorApi_Value));
  delay(500);
}
```

Pada tahap ini, fokus utama adalah mengamati nilai pembacaan sensor di Serial Monitor ketika lingkungan dalam kondisi normal dan ketika diberikan stimulus, seperti mendekatkan sumber gas (misalnya uap LPG) ke sensor gas atau nyala api kecil ke sensor api. Berdasarkan pengamatan, ditetapkan nilai ambang (threshold) awal untuk sensor gas, yaitu `sensorGas_Value > 400` dianggap sebagai indikasi adanya peningkatan konsentrasi gas yang berpotensi berbahaya, sedangkan untuk sensor api digunakan logika `sensorApi_Value == 1` sebagai indikator adanya api.

### 2. Pengujian Output (LED dan Buzzer)

Setelah sensor terverifikasi berfungsi, langkah berikutnya adalah menguji komponen output secara mandiri. Tujuannya untuk memastikan LED dan buzzer dapat dikendalikan oleh mikrokontroler dengan benar sebelum diterapkan logika alarm kebakaran.

Pengujian dilakukan dengan menyalakan dan mematikan LED serta buzzer secara berkala menggunakan kode sederhana:

```cpp
const int led_merah = 8;
const int buzzer    = 9;

void setup() {
  Serial.begin(9600);
  pinMode(led_merah, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(led_merah, LOW);
  digitalWrite(buzzer, LOW);
}

void loop() {
  digitalWrite(led_merah, HIGH);
  digitalWrite(buzzer, HIGH);
  Serial.println("LED & Buzzer: ON");
  delay(500);

  digitalWrite(led_merah, LOW);
  digitalWrite(buzzer, LOW);
  Serial.println("LED & Buzzer: OFF");
  delay(500);
}
```

Dari pengujian ini dapat dipastikan bahwa LED menyala dan padam dengan benar, serta buzzer menghasilkan bunyi beep secara periodik. Tahapan ini penting sebagai dasar sebelum mengaitkan perilaku LED dan buzzer dengan kondisi sensor gas dan api.

## Pembuatan Alat

Pada tahap pembuatan alat, sistem mulai mengintegrasikan pembacaan sensor dengan pengendalian LED dan buzzer untuk membentuk sebuah alarm kebakaran sederhana. Fokus utama masih pada versi konvensional (non-IoT), di mana peringatan hanya diberikan secara lokal melalui indikator visual dan audio.

### 1. Desain Logika Sistem

Logika sistem dirancang untuk membedakan beberapa kondisi berdasarkan kombinasi status sensor gas dan sensor api, dengan tujuan merepresentasikan tingkat bahaya yang berbeda. Secara ringkas, aturan logika yang digunakan adalah:

1. **Standby (tidak ada gas dan tidak ada api)**

   * `gasTerdeteksi == false` dan `apiTerdeteksi == false`
   * Buzzer **OFF**.
   * LED memberikan **pola heartbeat**: nyala singkat setiap beberapa detik sebagai indikator bahwa sistem aktif dan siaga.

2. **Hanya gas terdeteksi**

   * `gasTerdeteksi == true` dan `apiTerdeteksi == false`
   * LED **menyala terus** sebagai tanda adanya potensi bahaya.
   * Buzzer memberikan **beep jarang** (ON sebentar, OFF lebih lama) untuk menunjukkan peringatan tingkat awal terkait kebocoran atau peningkatan gas.

3. **Hanya api terdeteksi**

   * `gasTerdeteksi == false` dan `apiTerdeteksi == true`
   * LED dan buzzer **blink cepat secara bersamaan**, merepresentasikan kondisi bahaya yang lebih serius karena api telah terdeteksi.

4. **Gas dan api terdeteksi bersamaan**

   * `gasTerdeteksi == true` dan `apiTerdeteksi == true`
   * Buzzer menyala **non-stop (kontinu)** sebagai alarm maksimum.
   * LED **blink** dengan periode sedang, menegaskan bahwa sistem berada dalam kondisi bahaya tinggi.

Desain pola ini bersifat hierarkis: semakin tinggi tingkat bahaya, semakin intens pola bunyi dan kedipan yang dihasilkan. Pendekatan ini diharapkan memudahkan pengguna untuk mengenali tingkat bahaya hanya dari pola suara dan cahaya, bahkan ketika tidak melihat langsung layar monitor.

### 2. Implementasi Kode Sistem Alarm

Berikut adalah potongan kode yang mengintegrasikan pembacaan sensor gas dan api dengan logika aktivasi LED dan buzzer:

```cpp
// Input
const int sensor_gas = A0;
const int sensor_api = 3;

// Output
const int led_merah = 8;
const int buzzer    = 9;

// Variabel
float sensorGas_Value;
int sensorApi_Value;

const int ambangGas = 400;  // threshold gas terdeteksi

void setup() {
  Serial.begin(9600);
  pinMode(sensor_gas, INPUT);
  pinMode(sensor_api, INPUT);
  pinMode(led_merah, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(led_merah, LOW);
  digitalWrite(buzzer, LOW);
}

void loop() {
  // Baca nilai sensor
  sensorGas_Value = analogRead(sensor_gas);
  sensorApi_Value = !digitalRead(sensor_api);

  // Variabel logika
  bool gasTerdeteksi = sensorGas_Value > ambangGas;
  bool apiTerdeteksi = (sensorApi_Value == 1);

  Serial.print("Gas: ");
  Serial.println(sensorGas_Value);
  Serial.print("Api: ");
  Serial.println(sensorApi_Value);
  Serial.println();

  if (!gasTerdeteksi && !apiTerdeteksi) {
    // Mode standby: LED heartbeat, buzzer OFF
    digitalWrite(buzzer, LOW);

    digitalWrite(led_merah, HIGH);
    delay(100);
    digitalWrite(led_merah, LOW);
    delay(4900);
  }
  else if (gasTerdeteksi && !apiTerdeteksi) {
    // Gas terdeteksi: LED ON, buzzer beep jarang
    digitalWrite(led_merah, HIGH);

    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(1300);
  }
  else if (!gasTerdeteksi && apiTerdeteksi) {
    // Api terdeteksi: LED dan buzzer blink cepat
    digitalWrite(led_merah, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(200);

    digitalWrite(led_merah, LOW);
    digitalWrite(buzzer, LOW);
    delay(200);
  }
  else {
    // Gas dan api terdeteksi bersamaan: buzzer ON kontinu, LED blink
    digitalWrite(buzzer, HIGH);

    digitalWrite(led_merah, HIGH);
    delay(300);
    digitalWrite(led_merah, LOW);
    delay(300);
  }
}
```
