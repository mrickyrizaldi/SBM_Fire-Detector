// Pin output
const int led_merah = 8;
const int buzzer    = 9;

void setup() {
  Serial.begin(9600);

  pinMode(led_merah, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Awalnya mati
  digitalWrite(led_merah, LOW);
  digitalWrite(buzzer, LOW);
}

void loop() {
  // Nyalakan LED dan buzzer blink
  digitalWrite(led_merah, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(500);

  // Matikan LED dan buzzer
  digitalWrite(led_merah, LOW);
  digitalWrite(buzzer, LOW);
  delay(500);
}
