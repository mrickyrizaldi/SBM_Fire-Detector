const int relay = 6;
const int buzzer = 7;
const int led_merah = 8;

void setup() {
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led_merah, OUTPUT);

  // kondisi awal
  digitalWrite(relay, LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(led_merah, LOW);
}

void loop() {
  // test LED Heartbeat
  Serial.println("Mode Standby");
  for (int i = 0; i < 3; i++) {
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, LOW);

    digitalWrite(led_merah, HIGH);
    delay(100);
    digitalWrite(led_merah, LOW);
    delay(1900);
  }

  // test LED ON, buzzer beep jarang, relay OFF
  Serial.println("Mode Gas Terdeteksi");
  for (int i = 0; i < 5; i++) {
    digitalWrite(led_merah, HIGH);
    digitalWrite(relay, LOW);

    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(2000);
  }

  // test LED dan buzzer blink cepat serta relay OFF
  Serial.println("Mode Api Terdeteksi");
  for (int i = 0; i < 10; i++) {
    digitalWrite(relay, LOW);

    digitalWrite(led_merah, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);

    digitalWrite(led_merah, LOW);
    digitalWrite(buzzer, LOW);
    delay(500);
  }

  // test buzzer terus, LED blink sedang, relay ON
  Serial.println("Mode Gas + Api");
  for (int i = 0; i < 10; i++) {
    digitalWrite(relay, HIGH);
    digitalWrite(buzzer, HIGH);

    digitalWrite(led_merah, HIGH);
    delay(300);
    digitalWrite(led_merah, LOW);
    delay(300);
  }

  // Matikan semua
  digitalWrite(relay, LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(led_merah, LOW);
  delay(3000);
}
