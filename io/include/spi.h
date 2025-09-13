#ifndef SPI_H
#define SPI_H

#include "defines.h"
#include "haltypes.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

extern LIBRARY_EXPORT bool spi_init(void);  
extern LIBRARY_EXPORT bool spi_enumerate(hal_device_info_t *list, size_t *count);
extern LIBRARY_EXPORT bool spi_open(hal_device_id_t device_id);
extern LIBRARY_EXPORT bool spi_close(hal_device_id_t device_id);
extern LIBRARY_EXPORT bool spi_read(hal_device_id_t device_id, void* buffer, size_t size);
extern LIBRARY_EXPORT bool spi_write(hal_device_id_t device_id, const void* data, size_t size);
extern LIBRARY_EXPORT bool spi_set_mode(hal_device_id_t device_id, uint8_t mode);
extern LIBRARY_EXPORT bool spi_set_speed(hal_device_id_t device_id, uint32_t speed_hz);
extern LIBRARY_EXPORT bool spi_set_bits_per_word(hal_device_id_t device_id, uint8_t bits);
extern LIBRARY_EXPORT bool spi_set_timeout(hal_device_id_t device_id, uint32_t timeout_ms);
extern LIBRARY_EXPORT bool spi_flush(hal_device_id_t device_id);
extern LIBRARY_EXPORT bool spi_drain(hal_device_id_t device_id);


#ifdef __cplusplus
}
#endif

#endif // SPI_H
