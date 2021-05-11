#ifndef SMTP
#define SMTP

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "Mail.h"
#include "SecurityType.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LIBRARY_EXPORT __attribute__((visibility("default")))

typedef struct smtp_t smtp_t;

extern LIBRARY_EXPORT smtp_t* smtp_allocate(void);
extern LIBRARY_EXPORT void smtp_free(smtp_t* ptr);
extern LIBRARY_EXPORT void smtp_set_account_information(smtp_t* ptr, const char* hoststr, uint16_t portstr, const char* usernamestr, const char* passwordstr, SecurityType sectype);
extern LIBRARY_EXPORT void smtp_set_public_ip_address(smtp_t* ptr, const char* ip);
extern LIBRARY_EXPORT bool smtp_disconnect(smtp_t* ptr);
extern LIBRARY_EXPORT bool smtp_connect(smtp_t* ptr);
extern LIBRARY_EXPORT bool smtp_send_helo(smtp_t* ptr);
extern LIBRARY_EXPORT bool smtp_start_tls(smtp_t* ptr);
extern LIBRARY_EXPORT bool smtp_need_tls(smtp_t* ptr);
extern LIBRARY_EXPORT bool smtp_login(smtp_t* ptr);
extern LIBRARY_EXPORT bool smtp_logout(smtp_t* ptr);
extern LIBRARY_EXPORT bool smtp_sendmail(smtp_t* ptr, const mail_t* mail);
extern LIBRARY_EXPORT const char* smtp_get_account(smtp_t* ptr);
extern LIBRARY_EXPORT const char* smtp_get_error(smtp_t* ptr);

#ifdef __cplusplus
}
#endif

#endif
