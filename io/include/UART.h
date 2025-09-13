#ifndef UART_H
#define UART_H

#include "Defines.h"
#include "HALTypes.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum uart_parity_t 
{
    HAL_PARITY_NONE,
    HAL_PARITY_ODD,
    HAL_PARITY_EVEN
} uart_parity_t;

typedef enum uart_flow_control_t 
{
    HAL_FLOW_CONTROL_NONE,
    HAL_FLOW_CONTROL_RTS_CTS,  // Hardware flow control
    HAL_FLOW_CONTROL_XON_XOFF   // Software flow control
} uart_flow_control_t;

extern LIBRARY_EXPORT bool uart_init(void);
extern LIBRARY_EXPORT bool uart_enumerate(hal_device_info_t *list, size_t *count);
extern LIBRARY_EXPORT bool uart_open(hal_device_id_t device_id);
extern LIBRARY_EXPORT bool uart_close(hal_device_id_t device_id);
extern LIBRARY_EXPORT bool uart_read(hal_device_id_t device_id, void* buffer, size_t size);
extern LIBRARY_EXPORT bool uart_write(hal_device_id_t device_id, const void* data, size_t size);
extern LIBRARY_EXPORT bool uart_set_baudrate(hal_device_id_t device_id, uint32_t baudrate);
extern LIBRARY_EXPORT bool uart_set_parity(hal_device_id_t device_id, bool enable, uart_parity_t parity);
extern LIBRARY_EXPORT bool uart_set_stopbits(hal_device_id_t device_id, uint8_t stopbits);
extern LIBRARY_EXPORT bool uart_set_flow_control(hal_device_id_t device_id, bool enable, uart_flow_control_t flow_control);
extern LIBRARY_EXPORT bool uart_set_data_bits(hal_device_id_t device_id, uint8_t data_bits);
extern LIBRARY_EXPORT bool uart_set_timeout(hal_device_id_t device_id, uint32_t timeout_ms);
extern LIBRARY_EXPORT bool uart_flush(hal_device_id_t device_id);
extern LIBRARY_EXPORT bool uart_drain(hal_device_id_t device_id);

#ifdef __cplusplus
}
#endif

#endif // UART_H
