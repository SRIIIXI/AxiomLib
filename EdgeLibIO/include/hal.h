 
#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Device ID type
typedef enum hal_device_type_t{
    HAL_DEVICE_TYPE_GPIO,
    HAL_DEVICE_TYPE_UART,
    HAL_DEVICE_TYPE_I2C,
    HAL_DEVICE_TYPE_SPI,
    HAL_DEVICE_TYPE_ADC,
    HAL_DEVICE_TYPE_PWM,
    HAL_DEVICE_TYPE_CAN,
    HAL_DEVICE_TYPE_USB,
    HAL_DEVICE_TYPE_BLE_UART,   // BLE module over UART (e.g., HM-10, Nordic)
    HAL_DEVICE_TYPE_BLE_USB,    // BLE dongle over USB (e.g., CSR, Bluegiga)
    HAL_DEVICE_TYPE_UNKNOWN
} hal_device_type_t;

typedef uint16_t hal_device_id_t;

typedef struct hal_device_info_t{
    hal_device_type_t type;
    char path[256];              // e.g., "/dev/ttyUSB0"
    char name[64];               // logical name, e.g., "BLE_UART_1"
    uint32_t capabilities;       // bitmask of HAL_CAP_*
    void *metadata;              // optional vendor-specific info
} hal_device_info_t;

// Callback type for I/O events
typedef void (*hal_event_callback_t)(hal_device_id_t device_id, const void* data, size_t size);

// Initialization and teardown
int hal_open(void);     // Initialize all hardware interfaces
int hal_close(void);    // Shutdown and cleanup

// Device enumeration
int hal_enumerate(hal_device_info_t *device_list, size_t *num_devices);

// I/O operations
int hal_read(hal_device_id_t device_id, void* buffer, size_t size);
int hal_write(hal_device_id_t device_id, const void* data, size_t size);

// Device control
int hal_enable(hal_device_id_t device_id);   // Enable device (e.g., power up, activate)
int hal_disable(hal_device_id_t device_id);  // Disable device (e.g., power down, deactivate)

// Event registration
int hal_register_callback(hal_device_id_t device_id, hal_event_callback_t callback);

#ifdef __cplusplus
}
#endif

#endif // HAL_H
