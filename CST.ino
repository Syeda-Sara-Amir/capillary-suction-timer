#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int INNER_PIN_1 = 6;
const int INNER_PIN_2 = 7;
const int OUTER_PIN   = 8;
const int RESET_BTN   = 9;

bool timing  = false;
bool done    = false;
unsigned long startTime = 0;
float cstValue = 0.0;

void setup() {
  Serial.begin(9600);
  
  // INPUT_PULLUP means no external resistors needed
  pinMode(INNER_PIN_1, INPUT_PULLUP);
  pinMode(INNER_PIN_2, INPUT_PULLUP);
  pinMode(OUTER_PIN,   INPUT_PULLUP);
  pinMode(RESET_BTN,   INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  showReady();
}

void loop() {
  
  // Reset button
  if (digitalRead(RESET_BTN) == LOW) {
    delay(50);
    if (digitalRead(RESET_BTN) == LOW) {
      resetDevice();
    }
  }

  // Wait for start
  if (!timing && !done) {
    // With INPUT_PULLUP, detection is REVERSED
    // Dry = HIGH, Wet/bridged = LOW
    if (digitalRead(INNER_PIN_1) == LOW &&
        digitalRead(INNER_PIN_2) == LOW) {
      delay(10);
      if (digitalRead(INNER_PIN_1) == LOW &&
          digitalRead(INNER_PIN_2) == LOW) {
        startTime = millis();
        timing = true;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("TIMING...       ");
        lcd.setCursor(0, 1);
        lcd.print("                ");
      }
    }
  }

  // Timer running
  if (timing && !done) {
    float elapsed = (millis() - startTime) / 1000.0;
    lcd.setCursor(0, 1);
    lcd.print(elapsed, 2);
    lcd.print(" s          ");

    if (digitalRead(OUTER_PIN) == LOW) {
      delay(10);
      if (digitalRead(OUTER_PIN) == LOW) {
        cstValue = (millis() - startTime) / 1000.0;
        timing = false;
        done   = true;
        showResult(cstValue);
      }
    }
  }
}
 
void showReady() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CST TIMER READY ");
  lcd.setCursor(0, 1);
  lcd.print("Place sample... ");
}

void showResult(float val) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CST = ");
  lcd.print(val, 2);
  lcd.print(" s      ");
  lcd.setCursor(0, 1);
  lcd.print("Press RESET btn ");
}

void resetDevice() {
  timing   = false;
  done     = false;
  cstValue = 0.0;
  delay(200);
  showReady();
}
