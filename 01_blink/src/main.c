#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* Retrieve the Devicetree node identifier for alias "led0" */
#define LED0_NODE DT_ALIAS(led0)

/* Pull node properties into a C struct (GPIO controller pointer, pin number, flags) */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
    int ret;

    /* Verify driver readiness */
    if (!gpio_is_ready_dt(&led)) {
        return 0;
    }

    /* Configure GPIO pin direction */
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return 0;
    }

    while (1) {
        /* Toggle pin state */
        ret = gpio_pin_toggle_dt(&led);
        
        /* Yield thread execution for 500ms using the built-in kernel scheduler */
        k_msleep(500);
    }

    return 0;
}