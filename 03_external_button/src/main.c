#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/input/input.h>

#define STATUS_LED_NODE DT_ALIAS(external_led)
#define EXTERNAL_BUTTON_NODE DT_ALIAS(external_button)

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(EXTERNAL_BUTTON_NODE, gpios);
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(STATUS_LED_NODE, gpios);


int main(void) {
    if (!gpio_is_ready_dt(&button) || !gpio_is_ready_dt(&led)) {
        return 0;
    }

    int ret;

    ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
    if (ret != 0) {
        printk("Failed to configure button: %d\n", ret);
        return 0;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret != 0) {
        printk("Failed to configure LED: %d\n", ret);
        return 0;
    }

    int state = gpio_pin_get_dt(&button);
    int current_state = state;
    int toggle = false;

    while (1) {
        current_state = gpio_pin_get_dt(&button);
        if (state != current_state) {
            toggle = !toggle;
            state = current_state;
            k_msleep(50);
        }

        if (toggle) {
            gpio_pin_toggle_dt(&led);
            k_msleep(50);
        }
    }
}