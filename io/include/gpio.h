#ifndef GPIO_H
#define GPIO_H

#include "defines.h"
#include "haltypes.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

extern LIBRARY_EXPORT bool gpio_init(void);      // Initialize GPIO hardware
extern LIBRARY_EXPORT bool gpio_enumerate(hal_device_info_t *list, size_t *count);
extern LIBRARY_EXPORT bool gpio_read(hal_device_id_t device_id, void* buffer, size_t size); // Read data from GPIO
extern LIBRARY_EXPORT bool gpio_write(hal_device_id_t device_id, const void* data, size_t size); // Write data to GPIO

#ifdef __cplusplus
}
#endif

#endif // HAL_H
