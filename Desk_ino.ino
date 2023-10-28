#include <Arduino.h>
#include <avr/sleep.h>

#define OUT_PIN 6
#define PHOTO_PIN A0
#define WAKEUP_PIN 2
const int pin_w[] = { 13, 12, 11, 10 };

int l = 0;
uint8_t output_value = 0;
volatile byte flag = 1;

void setup() {
  //Serial.begin(9600);
  pinMode(WAKEUP_PIN, INPUT);
  pinMode(PHOTO_PIN, INPUT);
  pinMode(OUT_PIN, INPUT);
  led_opt(2);
  sleep();
}

void loop() {
  output_value = digitalRead(OUT_PIN);
  l = analogRead(PHOTO_PIN);
  //Serial.println(l);
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


void led_opt(int x) {
  switch (x) {
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

void wakeupCallback() {
  flag = 0;
}

void sleep() {
  //Serial.flush();
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  attachInterrupt(digitalPinToInterrupt(WAKEUP_PIN), wakeupCallback, RISING);
  delay(200);
  sleep_cpu();

  // codice eseguito dopo il risveglio
  detachInterrupt(digitalPinToInterrupt(WAKEUP_PIN));
  sleep_disable();
  digitalWrite(pin_w[0], HIGH);
  delay(200);
  digitalWrite(pin_w[0], LOW);
  loop();
}