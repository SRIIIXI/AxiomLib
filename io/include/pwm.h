#ifndef PWM_H
#define PWM_H

#include "defines.h"
#include "haltypes.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

extern LIBRARY_EXPORT bool pwm_init(void);          // Initialize PWM subsystem
extern LIBRARY_EXPORT bool pwm_enumerate(hal_device_info_t *list, size_t *count);
extern LIBRARY_EXPORT bool pwm_set_frequency(hal_device_id_t device_id, uint32_t frequency); // Set PWM frequency for a device
extern LIBRARY_EXPORT bool pwm_set_duty_cycle(hal_device_id_t device_id, float duty_cycle); // Set PWM duty cycle for a device
extern LIBRARY_EXPORT bool pwm_enable(hal_device_id_t device_id); // Enable PWM output
extern LIBRARY_EXPORT bool pwm_disable(hal_device_id_t device_id); // Disable PWM output   

#ifdef __cplusplus
}
#endif

#endif // HAL_H
