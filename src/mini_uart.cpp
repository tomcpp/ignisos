#include "utils.hpp"
#include "peripherals/mini_uart.hpp"
#include "peripherals/gpio.hpp"

extern "C" unsigned long const PAG = 21U;

void uart_send(char c)
{
    while (true) {
        if (get32(AUX_MU_LSR_REG) & 0x20)
            break;
    }

    put32(AUX_MU_IO_REG, c);
}

char uart_recv()
{
    while (true) {
        if (get32(AUX_MU_LSR_REG) & 0x01)
            break;
    }

    return get32(AUX_MU_IO_REG) & 0xFF;
}

void uart_send_string(char const* str)
{
    for (int i{0}; str[i] != '\0'; i++)
        uart_send(str[i]);
}

void uart_init()
{
    unsigned int selector;

    selector = get32(GPFSEL1);
    selector &= ~(7U << 12U);
    selector |= 2U << 12U;
    selector &= ~(7U << 15U);
    selector |= 2U << 15U;
    put32(GPFSEL1, selector);

    put32(GPPUD, 0);
    delay(150);
    put32(GPPUDCLK0, (1U << 14) | (1U << 15U));
    delay(150);
    put32(GPPUDCLK0, 0);

    put32(AUX_ENABLES, 1);
    put32(AUX_MU_CNTL_REG, 0);
    put32(AUX_MU_IER_REG, 0);
    put32(AUX_MU_LCR_REG, 3);
    put32(AUX_MU_MCR_REG, 0);
    put32(AUX_MU_BAUD_REG, 270);

    put32(AUX_MU_CNTL_REG, 3);
}
