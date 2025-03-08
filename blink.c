#include "pico/stdlib.h"

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 1000
#endif

// Perform initialisation
int pico_led_init(void) {
#if defined(PICO_DEFAULT_LED_PIN)
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
#endif
}

// Turn the led on or off
void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
    // Just set the GPIO on or off
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#endif
}

int main() {
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);
    
    while (true) {
        // Start with the initial delay
        uint32_t current_delay = LED_DELAY_MS;
        const float decay_factor = 0.9f;
        const int num_iterations = 100; // Number of on/off cycles in the pattern
        
        // Loop through the pattern iterations
        for (int i = 0; i < num_iterations; i++) {
            // Turn LED on
            pico_set_led(true);
            sleep_ms(current_delay);
            
            // Turn LED off
            pico_set_led(false);
            sleep_ms(current_delay);
            
            // Calculate next delay
            current_delay = (uint32_t)(current_delay * decay_factor);
        }
    }
}