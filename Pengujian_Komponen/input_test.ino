const int sensor_gas = A0;
const int sensor_api = 3;

float sensorGas_Value;
int sensorApi_Value; 

void setup() {
  // put your setup code here, to run once:
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
