#ifndef IRONMAN_H
#define IRONMAN_H

#define LED_COUNT 12      // number of leds present on your board
#define LED_PIN 4         // pin to be used to manage the leds
#define LED_BRIGHTNESS 10 // the default starting brightness
#define BTN_PIN 2         // pin to be used for button
#define BTN_DEBOUNCE 50   // button debounce

/**
 * Defining button structure
 */
struct button_t
{
    uint8_t current_state = HIGH;
    uint8_t previous_state;
    uint32_t debounce_time = 0;
};

/**
 * Initialize the led ring
 */
void initialize();

/**
 * Render hartbeat effect
 */
void hartbeat();

/**
 * Change ring color
 */
void changeColor();

#endif