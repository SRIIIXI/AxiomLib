 
#include "HAL.h"
#include "UART.h"
#include "SPI.h"
#include "I2C.h"
#include "PWM.h"
#include "GPIO.h"
#include "ADC.h"
#include "CAN.h"

static hal_device_info_t device_registry[MAX_DEVICES];
static size_t device_count = 0;
static bool hal_initialized = false;


bool hal_open(void)
{
    if (!hal_initialized)
    {
        return false;
    }

    int status = 0;

    status |= uart_init();
    status |= spi_init();
    status |= i2c_init();
    status |= i2c_init();
    status |= pwm_init();
    status |= gpio_init();
    status |= adc_init(); 
    status |= can_init();
  
    if (status == 0)
    {
        hal_initialized = true;
    }

    return status;
}

bool hal_close(void)
{
    // Optional: driver-specific shutdowns

    hal_initialized = false;
    device_count = 0;
    memset(device_registry, 0, sizeof(device_registry));

    return true;
}

bool hal_enumerate(hal_device_info_t *device_list, size_t *num_devices)
{
    if (!hal_initialized || !device_list || !num_devices)
    {
        return false;
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

     // ADC
    count = MAX_DEVICES - total;
    if (adc_enumerate(&device_list[total], &count) == 0)
    {
        total += count;
    }

    // GPIO
    count = MAX_DEVICES - total;
    if (gpio_enumerate(&device_list[total], &count) == 0)
    {
        total += count;
    }

    // PWM
    count = MAX_DEVICES - total;
    if (pwm_enumerate(&device_list[total], &count) == 0)
    {
        total += count;
    }

    // CAN
    count = MAX_DEVICES - total;            
    if (can_enumerate(&device_list[total], &count) == 0)
    {
        total += count;
    }   

    memcpy(device_registry, device_list, total * sizeof(hal_device_info_t));
    device_count = total;
    *num_devices = total;

    return true;
}
