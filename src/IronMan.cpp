#include <Arduino.h>
#include <FastLED.h>
#include <IronMan.h>

void (*state)() = initialize;

CRGB dots[LED_COUNT];
CRGB colors[] = {
  CRGB::White, 
  CRGB::Blue, 
  CRGB::Green, 
  CRGB::Yellow, 
  CRGB::Orange, 
  CRGB::Red,  
  CRGB::Black
};

button_t button;

unsigned char color_index = 0;

unsigned long hartbeat_uptime = 0;
signed char hartbeat_brightness_unit = 1;

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

  if (reading != button.previous_state)
  {
    button.debounce_time = millis();
  }

  if ((millis() - button.debounce_time) > BTN_DEBOUNCE)
  {
    if (reading != button.current_state)
    {
      button.current_state = reading;

      if (button.current_state == LOW)
      {
        changeColor();
      }
    }
  }

  button.previous_state = reading;

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
  if ((millis() - hartbeat_uptime) > 10)
  {
    hartbeat_uptime = millis();
    uint8_t brightness = FastLED.getBrightness();

    if (brightness == 10)
    {
      hartbeat_brightness_unit = 1;
    }
    else if (brightness == 255)
    {
      hartbeat_brightness_unit = -1;
    }

    FastLED.setBrightness(brightness + hartbeat_brightness_unit);
    FastLED.show();
  }
}

void changeColor()
{
  if (++color_index == (sizeof(colors) / sizeof(CRGB)))
  {
    color_index = 0;
  }

  for (uint8_t i = 0; i < LED_COUNT; i++)
  {
    dots[i] = colors[color_index];
  }
}