#include <SoftwareSerial.h>

// Bluetooth: RX, TX (Arduino)
SoftwareSerial bt(10, 11); // RX, TX

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

// variabel untuk menghindari spam kirim pesan
String lastState = "";

void setup() {
  Serial.begin(9600);   // Serial ke laptop
  bt.begin(9600);       // Serial ke Bluetooth

  pinMode(sensor_gas, INPUT);
  pinMode(sensor_api, INPUT);
  pinMode(led_merah, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(led_merah, LOW);
  digitalWrite(buzzer, LOW);
}

void kirimStatusBT(String state) {
  if (state != lastState) {
    lastState = state;

    bt.println(state);      // kirim ke Bluetooth
    Serial.print("Kirim BT: ");
    Serial.println(state);  // debug di Serial Monitor
  }
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
    // Standby
    kirimStatusBT("STATUS_AMAN");

    digitalWrite(buzzer, LOW);
    
    digitalWrite(led_merah, HIGH);
    delay(100);
    digitalWrite(led_merah, LOW);
    delay(2900);
  }

  else if (gasTerdeteksi && !apiTerdeteksi) {
    // Gas terdeteksi
    kirimStatusBT("ALERT_GAS");

    digitalWrite(led_merah, HIGH);

    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(1300);
  }

  else if (!gasTerdeteksi && apiTerdeteksi) {
    // Api terdeteksi
    kirimStatusBT("ALERT_API");

    digitalWrite(led_merah, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(200);

    digitalWrite(led_merah, LOW);
    digitalWrite(buzzer, LOW);
    delay(200);
  }

  else {
    // Gas dan api terdeteksi secara bersamaan
    kirimStatusBT("ALERT_GAS_DAN_API");

    digitalWrite(buzzer, HIGH);

    digitalWrite(led_merah, HIGH);
    delay(300);
    digitalWrite(led_merah, LOW);
    delay(300);
  }
}
