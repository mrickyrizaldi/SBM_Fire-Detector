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
