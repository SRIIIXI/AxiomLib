 
#ifndef HAL_TYPES_H
#define HAL_TYPES_H

#include "Defines.h"
#include <string.h>

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
    HAL_DEVICE_TYPE_BLE_HCI,    // BLE HCI interface (e.g., Bluetooth controller)
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

#define MAX_DEVICES 64
#define HAL_CAP_GPIO (1 << 0)
#define HAL_CAP_UART (1 << 1)
#define HAL_CAP_I2C (1 << 2)
#define HAL_CAP_SPI (1 << 3)
#define HAL_CAP_ADC (1 << 4)
#define HAL_CAP_PWM (1 << 5)
#define HAL_CAP_CAN (1 << 6)
#define HAL_CAP_USB (1 << 7)
#define HAL_CAP_BLE_UART (1 << 8)
#define HAL_CAP_BLE_USB (1 << 9)
#define HAL_CAP_BLE_HCI (1 << 10)
#define HAL_CAP_ALL (HAL_CAP_GPIO | HAL_CAP_UART | HAL_CAP_I2C | HAL_CAP_SPI | HAL_CAP_ADC | HAL_CAP_PWM | HAL_CAP_CAN | HAL_CAP_USB | HAL_CAP_BLE_UART | HAL_CAP_BLE_USB | HAL_CAP_BLE_HCI)

#ifdef __cplusplus
}
#endif

#endif // HAL_TYPES_H

