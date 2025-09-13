#include "SPI.h"

bool spi_init(void)
{
    return false;
}

bool spi_enumerate(hal_device_info_t *list, size_t *count)
{
    return false;
}

bool spi_open(hal_device_id_t device_id)
{
    return false;
}

bool spi_close(hal_device_id_t device_id)
{
    return false;
}

bool spi_read(hal_device_id_t device_id, void* buffer, size_t size)
{
    return false;
}

bool spi_write(hal_device_id_t device_id, const void* data, size_t size)
{
    return false;
}

bool spi_set_mode(hal_device_id_t device_id, uint8_t mode)
{
    return false;
}

bool spi_set_speed(hal_device_id_t device_id, uint32_t speed_hz)
{
    return false;
}   

bool spi_set_bits_per_word(hal_device_id_t device_id, uint8_t bits)
{
    return false;
}

bool spi_set_timeout(hal_device_id_t device_id, uint32_t timeout_ms)
{
    return false;
}

bool spi_flush(hal_device_id_t device_id)
{
    return false;
}

bool spi_drain(hal_device_id_t device_id)
{
    return false;
}
