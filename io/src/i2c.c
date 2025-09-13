#include "i2c.h"

bool i2c_init(void)
{
    return false;
}

bool i2c_enumerate(hal_device_info_t *list, size_t *count)
{
    return false;
}

bool i2c_open(hal_device_id_t device_id)
{
    return false;
}

bool i2c_close(hal_device_id_t device_id)
{
    return false;
}

bool i2c_read(hal_device_id_t device_id, void* buffer, size_t size)
{
    return false;
}

bool i2c_write(hal_device_id_t device_id, const void* data, size_t size)
{
    return false;
}

bool i2c_set_speed(hal_device_id_t device_id, uint32_t speed_hz)
{
    return false;
}

bool i2c_set_address(hal_device_id_t device_id, uint8_t address)
{
    return false;
}   

