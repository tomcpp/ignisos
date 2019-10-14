#include "mini_uart.hpp"

extern "C" void kernel_main()
{
    uart_init();
    uart_send_string("Hello, world!\r\n");

    while (true)
        uart_send(uart_recv());
}
