#ifndef IMAP
#define IMAP

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "Mail.h"
#include "SecurityType.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LIBRARY_EXPORT __attribute__((visibility("default")))

typedef struct imap_t imap_t;

extern LIBRARY_EXPORT imap_t* imap_allocate(void);
extern LIBRARY_EXPORT void imap_free(imap_t* ptr);
extern LIBRARY_EXPORT void imap_set_account_information(imap_t* ptr, const char* hoststr, uint16_t portstr, const char* usernamestr, const char* passwordstr, SecurityType sectype);
extern LIBRARY_EXPORT bool imap_connect(imap_t* ptr);
extern LIBRARY_EXPORT bool imap_login(imap_t* ptr);
extern LIBRARY_EXPORT bool imap_disconnect(imap_t* ptr);
extern LIBRARY_EXPORT bool imap_logout(imap_t* ptr);
extern LIBRARY_EXPORT bool imap_get_directory_list(imap_t* ptr, const char** dirList);
extern LIBRARY_EXPORT bool imap_get_capabilities(imap_t* ptr);
extern LIBRARY_EXPORT bool imap_get_directory(imap_t* ptr, const char* dirname, unsigned long emailCount, unsigned long uidNext);
extern LIBRARY_EXPORT bool imap_select_directory(imap_t* ptr, const char* dirname);
extern LIBRARY_EXPORT bool imap_get_emails_since(imap_t* ptr, const char* dirname, const char* fromdate, const char* uidlist);
extern LIBRARY_EXPORT bool imap_get_emails_prior(imap_t* ptr, const char* dirname, const char* fromdate, const char* uidlist);
extern LIBRARY_EXPORT bool imap_get_emails_recent(imap_t* ptr, const char* dirname, const char* uidlist);
extern LIBRARY_EXPORT bool imap_get_emails_all(imap_t* ptr, const char* dirname, const char* uidlist);
extern LIBRARY_EXPORT bool imap_get_message_header(imap_t* ptr, const char* uid, mail_t* mail);
extern LIBRARY_EXPORT bool imap_get_message_body(imap_t* ptr, const char* uid, mail_t* mail);
extern LIBRARY_EXPORT bool imap_delete_message(imap_t* ptr, const char* uid);
extern LIBRARY_EXPORT bool imap_flag_message(imap_t* ptr, const char* uid, const char* flag);
extern LIBRARY_EXPORT bool imap_mark_as_seen(imap_t* ptr, const char* uid);
extern LIBRARY_EXPORT bool imap_expunge(imap_t* ptr, const char* dir);
extern LIBRARY_EXPORT const char* imap_get_error(imap_t* ptr);
extern LIBRARY_EXPORT const char* imap_get_account(imap_t* ptr);

#ifdef __cplusplus
}
#endif

#endif
