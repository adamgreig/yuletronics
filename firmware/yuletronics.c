#include <stdint.h>
#include <stdbool.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define LED1 GPIO0
#define LED2 GPIO1
#define LED3 GPIO2
#define LED4 GPIO3
#define LED5 GPIO4
#define LED6 GPIO6
#define LED7 GPIO7
#define LED8 GPIO1

#define LED1_PORT GPIOA
#define LED2_PORT GPIOA
#define LED3_PORT GPIOA
#define LED4_PORT GPIOA
#define LED5_PORT GPIOA
#define LED6_PORT GPIOA
#define LED7_PORT GPIOA
#define LED8_PORT GPIOB

static const uint16_t led_pins[] = {
    0,
    LED1, LED2, LED3, LED4, LED5, LED6, LED7, LED8
};

static const uint32_t led_ports[] = {
    0,
    LED1_PORT, LED2_PORT, LED3_PORT, LED4_PORT,
    LED5_PORT, LED6_PORT, LED7_PORT, LED8_PORT
};

#define TURNON(led) gpio_set(led_ports[led], led_pins[led])
#define TURNOFF(led) gpio_clear(led_ports[led], led_pins[led])

static void gpio_setup(void)
{
    int led;

    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);

    for(led=1; led<=8; led++) {
        gpio_clear(led_ports[led], led_pins[led]);
        gpio_mode_setup(
            led_ports[led], GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, led_pins[led]);
        gpio_set_output_options(
            led_ports[led], GPIO_OTYPE_PP, GPIO_OSPEED_LOW, led_pins[led]);
    }
}

static void wait(void)
{
    volatile int i;
    for(i=0; i<100000; i++);
}

int main(void)
{
    gpio_setup();

    while(true)
    {
        TURNON(1);
        TURNON(5);
        wait();
        TURNON(3);
        TURNON(7);
        wait();
        TURNOFF(1);
        TURNOFF(5);
        wait();
        TURNOFF(3);
        TURNOFF(7);
        TURNON(2);
        TURNON(8);
        wait();
        TURNOFF(2);
        TURNOFF(8);
    }
    return 0;
}
