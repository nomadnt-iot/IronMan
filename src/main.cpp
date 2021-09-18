#include <Arduino.h>
#include <FastLED.h>
#include <config.h>

CRGB dots[LED_COUNT];

void initialize();
void hartbeat();
void changeColor();
void (*state)() = initialize;

uint8_t lastButtonState = HIGH;
uint8_t buttonState;
unsigned long lastDebounceTime = 0;

uint8_t color = 0;
CRGB colors[] = {CRGB::White, CRGB::Blue, CRGB::Green, CRGB::Yellow, CRGB::Orange, CRGB::Red, CRGB::Pink, CRGB::Black};

uint32_t upTime = 0;
int8_t rising = 1;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(dots, LED_COUNT);
  FastLED.setBrightness(LED_BRIGHTNESS);
  FastLED.clear();

  initialize();
}

void loop()
{
  uint8_t reading = digitalRead(BTN_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > BTN_DEBOUNCE) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        changeColor();
      }
    }
  }

  state();
}

void initialize()
{
  for (uint8_t i = 0; i < LED_COUNT; i++)
  {
    dots[i] = CRGB::White;
    FastLED.show();
    delay(200);
  }

  state = hartbeat;
}

void hartbeat()
{
  if ((millis() - upTime) > 10)
  {
    upTime = millis();

    if (FastLED.getBrightness() == 10)
    {
      rising = 1;
    }
    else if (FastLED.getBrightness() == 255)
    {
      rising = -1;
    }

    FastLED.setBrightness(FastLED.getBrightness() + rising);
    FastLED.show();
  }
}

void changeColor()
{
  color++;
  if (color == 8) color = 0;
        
  for (uint8_t i = 0; i < LED_COUNT; i++)
  {
    dots[i] = colors[color];
  }
}