#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define STATUS_LED_NODE DT_ALIAS(external_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(STATUS_LED_NODE, gpios);

int main(void)
{
    if (!gpio_is_ready_dt(&led)) {
        return 0;
    }

    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    while (1) {
        gpio_pin_toggle_dt(&led);
        k_msleep(500);
    }

    return 0;
}