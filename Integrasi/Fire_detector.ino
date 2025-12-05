// Input
const int sensor_gas = A0;
const int sensor_api = 3;

// Output
const int relay     = 6;
const int buzzer    = 7;
const int led_merah = 8;

// Variabel
float sensorGas_Value;
int sensorApi_Value;

const int ambangGas = 400;  // threshold gas terdeteksi

void setup() {
  Serial.begin(9600);
  pinMode(sensor_gas, INPUT);
  pinMode(sensor_api, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led_merah, OUTPUT);

  // kondisi awal
  digitalWrite(relay, LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(led_merah, LOW);
}

void loop() {
  // Baca nilai sensor
  sensorGas_Value = analogRead(sensor_gas);
  sensorApi_Value = !digitalRead(sensor_api);

  // Variabel logika
  bool gasTerdeteksi = sensorGas_Value > ambangGas;
  bool apiTerdeteksi = (sensorApi_Value == 1);

  // Debug ke Serial Monitor
  Serial.print("Gas: ");
  Serial.println(sensorGas_Value);
  Serial.print("Api: ");
  Serial.println(sensorApi_Value);
  Serial.println();

  if (!gasTerdeteksi && !apiTerdeteksi) {
    // standby
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, LOW);

    digitalWrite(led_merah, HIGH);
    delay(100);
    digitalWrite(led_merah, LOW);
    delay(1900);
  }

  else if (gasTerdeteksi && !apiTerdeteksi) {
    // Gas terdeteksi
    digitalWrite(relay, LOW);
    digitalWrite(led_merah, HIGH);

    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(2000);
  }

  else if (!gasTerdeteksi && apiTerdeteksi) {
    // Api terdeteksi
    digitalWrite(relay, LOW);

    digitalWrite(led_merah, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);

    digitalWrite(led_merah, LOW);
    digitalWrite(buzzer, LOW);
    delay(500);
  }

  else {
    // Gas dan api terdeteksi secara bersamaan
    digitalWrite(relay, HIGH);
    digitalWrite(buzzer, HIGH);

    digitalWrite(led_merah, HIGH);
    delay(300);
    digitalWrite(led_merah, LOW);
    delay(300);
  }
}
