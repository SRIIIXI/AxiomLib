 
#ifndef HAL_H
#define HAL_H

#include "defines.h"
#include "haltypes.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// Initialization and teardown
extern LIBRARY_EXPORT bool hal_open(void);     // Initialize all hardware interfaces
extern LIBRARY_EXPORT bool hal_close(void);    // Shutdown and cleanup

// Device enumeration
extern LIBRARY_EXPORT bool hal_enumerate(hal_device_info_t *device_list, size_t *num_devices);

// I/O operations
extern LIBRARY_EXPORT bool hal_read(hal_device_id_t device_id, void* buffer, size_t size);
extern LIBRARY_EXPORT bool hal_write(hal_device_id_t device_id, const void* data, size_t size);

// Device control
extern LIBRARY_EXPORT bool hal_enable(hal_device_id_t device_id);   // Enable device (e.g., power up, activate)
extern LIBRARY_EXPORT bool hal_disable(hal_device_id_t device_id);  // Disable device (e.g., power down, deactivate)

// Event registration
extern LIBRARY_EXPORT bool hal_register_callback(hal_device_id_t device_id, hal_event_callback_t callback);

#ifdef __cplusplus
}
#endif

#endif // HAL_H
