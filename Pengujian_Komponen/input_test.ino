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
