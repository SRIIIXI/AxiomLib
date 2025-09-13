#ifndef ADC_H
#define ADC_H

#include "defines.h"
#include "haltypes.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

extern LIBRARY_EXPORT bool adc_init(void);      // Initialize ADC hardware
extern LIBRARY_EXPORT bool adc_enumerate(hal_device_info_t *list, size_t *count);
extern LIBRARY_EXPORT bool adc_read(hal_device_id_t device_id, void* buffer, size_t size); // Read data from ADC
extern LIBRARY_EXPORT bool adc_write(hal_device_id_t device_id, const void* data, size_t size); // Write data to ADC    

#ifdef __cplusplus
}
#endif

#endif // ADC_H
