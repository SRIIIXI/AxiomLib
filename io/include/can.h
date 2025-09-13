#ifndef CAN_H
#define CAN_H

#include "defines.h"
#include "haltypes.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

extern LIBRARY_EXPORT bool can_init(void);      // Initialize CAN hardware
extern LIBRARY_EXPORT bool can_enumerate(hal_device_info_t *list, size_t *count);
extern LIBRARY_EXPORT bool can_read(hal_device_id_t device_id, void* buffer, size_t size); // Read data from CAN
extern LIBRARY_EXPORT bool can_write(hal_device_id_t device_id, const void* data, size_t size); // Write data to CAN   

#ifdef __cplusplus
}
#endif

#endif // CAN_H
