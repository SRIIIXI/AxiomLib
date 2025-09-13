#ifndef I2C_H
#define I2C_H

#include "Defines.h"
#include "HALTypes.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

extern LIBRARY_EXPORT bool i2c_init(void);
extern LIBRARY_EXPORT bool i2c_enumerate(hal_device_info_t *list, size_t *count);
extern LIBRARY_EXPORT bool i2c_open(hal_device_id_t device_id);
extern LIBRARY_EXPORT bool i2c_close(hal_device_id_t device_id);
extern LIBRARY_EXPORT bool i2c_read(hal_device_id_t device_id, void* buffer, size_t size);
extern LIBRARY_EXPORT bool i2c_write(hal_device_id_t device_id, const void* data, size_t size);
extern LIBRARY_EXPORT bool i2c_set_speed(hal_device_id_t device_id, uint32_t speed_hz);
extern LIBRARY_EXPORT bool i2c_set_address(hal_device_id_t device_id, uint8_t address); 

#ifdef __cplusplus
}
#endif

#endif // I2C_H
