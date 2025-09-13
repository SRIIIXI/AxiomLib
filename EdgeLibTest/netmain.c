#include <stdio.h>
#include <malloc.h>
#include "SecurityType.h"
#include "Smtp.h"

int main(int argc, char* argv[])
{
    smtp_resolve_public_ip_address();

    smtp_t* smtp = smtp_allocate();
    if(smtp == NULL)
    {
        printf("Failed to allocate SMTP instance\n");
        return 1;
    }

    const char* host = "smtp.example.com";
    uint16_t port = 25;
    const char* username = "";
    const char* password = "";
    security_type_t secType = None;

    smtp_set_account_information(smtp, host, port, username, password, secType);

    if(!smtp_connect(smtp))
    {
        printf("Failed to connect: %s\n", smtp_get_error(smtp));
        smtp_free(smtp);
        return 1;
    } 

    if(!smtp_send_helo(smtp))
    {
        printf("Failed to send HELO: %s\n", smtp_get_error(smtp));
        smtp_free(smtp);
        return 1;
    }
    
    if(smtp_need_tls(smtp))
    {
        printf("Server requires STARTTLS\n");
        if(!smtp_start_tls(smtp))
        {
            printf("Failed to start TLS: %s\n", smtp_get_error(smtp));  
        }
        else
        {
            printf("TLS started successfully\n");
        }
    }
    else
    {
        printf("Server does not require STARTTLS\n");
    }
    
    if(!smtp_login(smtp))
    {
        printf("Failed to login: %s\n", smtp_get_error(smtp));
        smtp_free(smtp);
        return 1;
    }
    printf("Logged in successfully\n");

    // Here you would typically prepare a mail_t object and send an email
    // For this example, we will skip that part

    if(!smtp_logout(smtp))
    {
        printf("Failed to logout: %s\n", smtp_get_error(smtp));
        smtp_free(smtp);
        return 1;
    }
    printf("Logged out successfully\n");

    if(!smtp_disconnect(smtp))
    {
        printf("Failed to disconnect: %s\n", smtp_get_error(smtp));
        smtp_free(smtp);
        return 1;
    }
    printf("Disconnected successfully\n");  


    smtp_free(smtp);

    return 0;
}