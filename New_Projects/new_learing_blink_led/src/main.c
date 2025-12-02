#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/devicetree.h>

#define SLEEP_NORMAL 1000
#define SLEEP_FAST   200

static struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);

int main(void)
{

    if (!device_is_ready(led.port) || !device_is_ready(button.port)) {
        return 0;
    }

    gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&button, GPIO_INPUT | GPIO_PULL_UP);

    while (1) {
        int val = gpio_pin_get_dt(&button);

        if (val == 0) {
            printk("Button pressed! Fast blink\n");
            gpio_pin_toggle_dt(&led);
            k_msleep(SLEEP_FAST);
        } else {
            gpio_pin_toggle_dt(&led);
            k_msleep(SLEEP_NORMAL);
        }
    }
}
