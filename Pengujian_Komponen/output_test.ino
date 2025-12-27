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
