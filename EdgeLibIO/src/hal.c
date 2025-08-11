 
#include "hal.h"
#include <string.h>
#include <stdbool.h>

#define MAX_DEVICES 64
static hal_device_info_t device_registry[MAX_DEVICES];
static size_t device_count = 0;
static bool hal_initialized = false;

// Forward declarations
extern int uart_init(void);
extern int spi_init(void);
extern int i2c_init(void);

extern int pwm_init(void);
extern int dio_init(void);
extern int aio_init(void);


extern int uart_enumerate(hal_device_info_t *list, size_t *count);
extern int spi_enumerate(hal_device_info_t *list, size_t *count);
extern int i2c_enumerate(hal_device_info_t *list, size_t *count);

int hal_open(void)
{
    if (hal_initialized)
    {
        return 0;
    }

    int status = 0;

    status |= uart_init();
    status |= spi_init();
    status |= i2c_init();

    if (status == 0)
    {
        hal_initialized = true;
    }

    return status;
}

int hal_close(void)
{
    // Optional: driver-specific shutdowns

    hal_initialized = false;
    device_count = 0;
    memset(device_registry, 0, sizeof(device_registry));

    return 0;
}

int hal_enumerate(hal_device_info_t *device_list, size_t *num_devices)
{
    if (!hal_initialized || !device_list || !num_devices)
    {
        return -1;
    }

    size_t total = 0;
    size_t count;

    // UART
    count = MAX_DEVICES - total;
    if (uart_enumerate(&device_list[total], &count) == 0)
    {
        total += count;
    }

    // SPI
    count = MAX_DEVICES - total;
    if (spi_enumerate(&device_list[total], &count) == 0)
    {
        total += count;
    }

    // I2C
    count = MAX_DEVICES - total;
    if (i2c_enumerate(&device_list[total], &count) == 0)
    {
        total += count;
    }

    memcpy(device_registry, device_list, total * sizeof(hal_device_info_t));
    device_count = total;
    *num_devices = total;

    return 0;
}
