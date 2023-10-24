#define OUT_PIN 6
#define PHOTO_PIN A0
const int pin_w[] = { 13, 12, 11, 10 };
int l = 0;
uint8_t output_value = 0;

void setup() {
  //Serial.begin(9600);
  delay(1500);
  pinMode(PHOTO_PIN, INPUT);
  pinMode(OUT_PIN, INPUT);
  led_opt(2);
}

void loop() {
  output_value = digitalRead(OUT_PIN);
  l = analogRead(PHOTO_PIN);
  Serial.println(l);
  if (l < 2) {
    if (output_value) {
        led_opt(1);
        delay(10000);
    } else {
      led_opt(0);
      }
  } else {
    led_opt(0);
  }
}


void led_opt(int x){
  switch(x){
    case 0:
    for (int i = 0; i < 4; i++) {
      digitalWrite(pin_w[i], LOW);
    }
    break;
    case 1: 
      for (int i = 0; i < 4; i++) {
        digitalWrite(pin_w[i], HIGH);
      }
      break;
    case 2:
      for (int i = 0; i < 4; i++) {
        pinMode(pin_w[i], OUTPUT);
      }
      break;
  }
}