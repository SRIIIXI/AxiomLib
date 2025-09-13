#include "uart.h"

bool uart_init(void)
{
    return false;
}

bool uart_enumerate(hal_device_info_t *list, size_t *count)
{
    return false;
}

bool uart_open(hal_device_id_t device_id)
{
    return false;
}

bool uart_close(hal_device_id_t device_id)
{
    return false;
}

bool uart_read(hal_device_id_t device_id, void* buffer, size_t size)
{
    return false;
}

bool uart_write(hal_device_id_t device_id, const void* data, size_t size)
{
    return false;
}

bool uart_set_baudrate(hal_device_id_t device_id, uint32_t baudrate)
{
    return false;
}

bool uart_set_parity(hal_device_id_t device_id, bool enable, uart_parity_t parity)
{
    return false;
}

bool uart_set_stopbits(hal_device_id_t device_id, uint8_t stopbits)
{
    return false;
}

bool uart_set_flow_control(hal_device_id_t device_id, bool enable, uart_flow_control_t flow_control)
{
    return false;
}

bool uart_set_data_bits(hal_device_id_t device_id, uint8_t data_bits)
{
    return false;
}

bool uart_set_timeout(hal_device_id_t device_id, uint32_t timeout_ms)
{
    return false;
}

bool uart_flush(hal_device_id_t device_id)
{
    return false;
}

bool uart_drain(hal_device_id_t device_id)
{
    return false;
}

