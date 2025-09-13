/*
BSD 2-Clause License

Copyright (c) 2017, Subrato Roy (subratoroy@hotmail.com)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "Smtp.h"
#include "StringEx.h"
#include "Responder.h"
#include "Dictionary.h"

#include <memory.h>
#include <netdb.h>

typedef struct smtp_t
{
    char host[33];
    char username[33];
    char password[33];
    uint16_t port;
    bool start_tls;
    const char* public_ip_address;
    security_type_t securityType;
    char errorStr[65];
    dictionary_t* email_header;
    mail_body_t* email_body;
    
    //responder_ssl_t* bearer;
    responder_t* bearer;
}smtp_t;

smtp_t* smtp_allocate(void)
{
    smtp_t* ptr = (smtp_t*)malloc(sizeof(smtp_t));

    if (ptr)
    {
        memset(ptr, 0, sizeof(smtp_t));
        ptr->port = 25;
        ptr->securityType = None;
        ptr->bearer = NULL;
        ptr->email_body = NULL;
        ptr->email_header = NULL;
        ptr->public_ip_address = NULL;
        ptr->start_tls = false;
        ptr->errorStr[0] = 0;
        return ptr;
    }   

    return NULL;
}

void smtp_free(smtp_t* ptr)
{
    if (ptr)
    {
        if (ptr->email_body)
        {
            free(ptr->email_body);
            ptr->email_body = NULL;
        }

        if (ptr->email_header)
        {
            free(ptr->email_header);
            ptr->email_header = NULL;
        }

        if (ptr->bearer)
        {
            free(ptr->bearer);
            ptr->bearer = NULL;
        }

        free(ptr);
        ptr = NULL;
    }
}



void smtp_set_account_information(smtp_t* ptr, const char* hoststr, uint16_t portstr, const char* usernamestr, const char* passwordstr, security_type_t sectype)
{
    if (ptr == NULL)
    {
        return;
    }   

    strncpy(ptr->host, hoststr, 32);
    ptr->host[32] = 0;
    strncpy(ptr->username, usernamestr, 32);
    ptr->username[32] = 0;
    strncpy(ptr->password, passwordstr, 32);
    ptr->password[32] = 0;
    ptr->port = portstr;
    ptr->securityType = sectype;
}

bool smtp_connect(smtp_t* ptr)
{
    if( ptr == NULL)
    {
        return false;
    }   
    // Initialize the responder (bearer) here based on securityType

    if (ptr->securityType == Ssl) 
    {
        //ptr->bearer = responder_ssl_allocate();
    } 
    else
    {
        ptr->bearer = responder_allocate();
    }

    if (ptr->bearer == NULL) 
    {
        snprintf(ptr->errorStr, sizeof(ptr->errorStr), "Failed to allocate responder");
        return false;
    }

    ptr->bearer = responder_create_socket(ptr->bearer, ptr->host, ptr->port);
    if (ptr->bearer == NULL) 
    {
        snprintf(ptr->errorStr, sizeof(ptr->errorStr), "Failed to create socket");
        return false;
    }

    bool connected = responder_connect_socket(ptr->bearer);

    if (!connected) 
    {
        snprintf(ptr->errorStr, sizeof(ptr->errorStr), "Failed to connect to server");
        return false;
    }
    return true;
}

bool smtp_disconnect(smtp_t* ptr)
{
    if (ptr == NULL || ptr->bearer == NULL) 
    {
        return false;
    }   

    bool closed = responder_close_socket(ptr->bearer);

    if (!closed) 
    {
        snprintf(ptr->errorStr, sizeof(ptr->errorStr), "Failed to close connection");
        return false;
    }

    return true;
}

bool smtp_send_helo(smtp_t* ptr)
{
    char* selfIp = "127.0.0.1";

    char tx_buffer[128] = { 0 };
    sprintf(tx_buffer, "EHLO %s\r\n", selfIp);

    if (!responder_send_string(ptr->bearer, tx_buffer))
    {
        snprintf(ptr->errorStr, sizeof(ptr->errorStr), "Failed to send EHLO");
        return false;
    }

    char* rx_buffer = NULL;

    responder_receive_string(ptr->bearer, &rx_buffer, "\r\n");

    if(strstr(rx_buffer, "STARTTLS") != NULL)
    {
        ptr->start_tls = true;
    }
    else
    {
        ptr->start_tls = false;
    }

    free(rx_buffer);

    return false;
}

void smtp_set_public_ip_address(smtp_t* ptr, const char* ip)
{
    //publicIp = ip;
}

const char* smtp_get_account(smtp_t* ptr)
{
    return NULL;
}

const char* smtp_get_error(smtp_t* ptr)
{
    return NULL;
}

bool smtp_sendmail(smtp_t* ptr, const mail_t* mail)
{
    return false;
//	std::vector<std::string> all_rcpt;

//	for (auto s : mail.Header.GetToList())
//	{
//		all_rcpt.push_back(s);
//	}

//	for (auto s : mail.Header.GetCcList())
//	{
//		all_rcpt.push_back(s);
//	}

//	for (auto s : mail.Header.GetBccList())
//	{
//		all_rcpt.push_back(s);
//	}

//	long pending_rcpt = all_rcpt.size();
//	long sent = 0;

//    bool ret = false;
//	std::string resp;
//	char buff[128] = { 0 };

//	memset(buff, 0, 128);
//	sprintf(buff, "MAIL FROM: <%s>\r\n", username.c_str());

//	bearer.SendString(buff);

//	while (true)
//	{
//		if (!bearer.ReceiveString(resp))
//		{
//			return false;
//		}

//		// FROM is verified
//		if (strcontains(resp.c_str(), "250 2.1.0"))
//		{
//			memset(buff, 0, 128);
//			sprintf(buff, "RCPT TO: <%s>\r\n", all_rcpt[sent].c_str());
//			bearer.SendString(buff);
//			sent++;
//			continue;
//		}

//		// RCPT TO is verified
//		if (strcontains(resp.c_str(), "250 2.1.5"))
//		{
//			if (pending_rcpt == sent)
//			{
//				memset(buff, 0, 128);
//				sprintf(buff, "DATA\r\n");
//				bearer.SendString(buff);
//			}
//			else
//			{
//				memset(buff, 0, 128);
//				sprintf(buff, "RCPT TO: <%s>\r\n", all_rcpt[sent].c_str());
//				bearer.SendString(buff);
//				sent++;
//			}
//			continue;
//		}

//		if (strcontains(resp.c_str(), "354"))
//		{
//			if (mail.SerializedData.length() < 1)
//			{
//				mail.Serialize();
//			}

//			bearer.SendString(mail.SerializedData);
//			bearer.SendString("\r\n.\r\n");
//			continue;
//		}

//		if (strcontains(resp.c_str(), "250 2.0.0"))
//		{
//			ret = true;
//			break;
//		}
//	}

//	return ret;
}

bool smtp_start_tls(smtp_t* ptr)
{
    return false;

//	std::string resp;
//	char buff[128] = { 0 };
//	sprintf(buff, "STARTTLS\r\n");

//	bearer.SendString(buff);

//	bool handshake_ok = false;

//	while (true)
//	{
//		if (!bearer.ReceiveString(resp))
//		{
//			return false;
//		}

//		if (strcontains(resp.c_str(), "220"))
//		{
//			handshake_ok = true;
//		}

//		if (bearer.PendingPreFetchedBufferSize() < 1)
//		{
//			break;
//		}
//	}

//	return bearer.SwitchToSecureMode();
}

bool smtp_need_tls(smtp_t* ptr)
{
    if(ptr == NULL)
    {
        return false;
    }   

    return ptr->start_tls;
}

bool smtp_login(smtp_t* ptr)
{
//	std::string resp;
//	std::vector<std::string> tokens;

//	char buff[128] = { 0 };

//	sprintf(buff, "AUTH LOGIN\r\n");
//	int len = (int)strlen(buff);

//	bearer.SendString(buff);

//	while (true)
//	{
//		if (!bearer.ReceiveString(resp))
//		{
//			return false;
//		}

//		//Authentication challenge
//		if (strcontains(resp.c_str(), "334"))
//		{
//			strremove(resp, '\n');
//			strremove(resp, '\r');
//			tokens.clear();
//			strsplit(resp, tokens, ' ');

//			class Base64 codec_b64;
//			std::string decoded_str;
//			unsigned long olen;
//			decoded_str = (char*)codec_b64.DecodeBase64(tokens[1].c_str(), tokens[1].length(), olen);
//			decoded_str[olen] = 0;

//			if (strcontains(decoded_str.c_str(), "Username"))
//			{
//				std::string encoded_uname;
//				codec_b64.EncodeBase64((unsigned char*)username.c_str(), username.length(), olen, encoded_uname);
//				encoded_uname += "\r\n";
//				bearer.SendString(encoded_uname);
//				continue;
//			}

//			if (strcontains(decoded_str.c_str(), "Password"))
//			{
//				std::string encoded_password;
//				codec_b64.EncodeBase64((unsigned char*)password.c_str(), password.length(), olen, encoded_password);
//				encoded_password += "\r\n";
//				bearer.SendString(encoded_password);
//				continue;
//			}
//		}

//		if (bearer.PendingPreFetchedBufferSize() < 1)
//		{
//			tokens.clear();
//			strsplit(resp, tokens, ' ');
			
//			if (tokens[0] == "235")
//			{
//				return true;
//			}

//			break;
//		}
//	}

	return false;
}

bool smtp_logout(smtp_t* ptr)
{
    if( ptr == NULL)
    {
        return false;
    }   

	char tx_buffer[128] = { 0 };
	sprintf(tx_buffer, "QUIT\r\n");

    responder_send_string(ptr->bearer, tx_buffer);

    char* rx_buffer = NULL; 
    responder_receive_string(ptr->bearer, &rx_buffer, "\r\n");

    //Check if the response contains "221"
    if(strstr(rx_buffer, "221") == NULL)
    {
        snprintf(ptr->errorStr, sizeof(ptr->errorStr), "Failed to logout");
        return false;   
    }

    free(rx_buffer);

	return true;
}

bool smtp_is_connected(smtp_t* ptr)
{
    if( ptr == NULL || ptr->bearer == NULL)
    {
        return false;
    }   

    return responder_is_connected(ptr->bearer); 
}

bool smtp_resolve_public_ip_address()
{
    responder_t* http_client = responder_allocate();

    if (http_client == NULL) 
    {
        return false;
    }

    http_client = responder_create_socket(http_client, "whatismyip.akamai.com", 80);

    if (http_client == NULL) 
    {
        return false;
    }

    bool connected = responder_connect_socket(http_client);

    if (!connected) 
    {
        printf("Failed to connect to whatismyip.akamai.com");
        return false;
    }

    char tx_buffer[128] = { 0 };
    sprintf(tx_buffer, "GET / HTTP/1.0\r\nHost: whatismyip.akamai.com\r\n\r\n");

    if (!responder_send_string(http_client, tx_buffer))
    {
        printf("Failed to send HTTP GET");
        return false;
    }

    char* rx_buffer = NULL;

    // This call reads the HTTP headers
    responder_receive_string(http_client, &rx_buffer, "\r\n\r\n");
    free(rx_buffer);
    rx_buffer = NULL;

    // This call reads the body which contains the public IP address
    size_t remaining = responder_get_prefetched_buffer_size(http_client);
    responder_receive_buffer(http_client, &rx_buffer, remaining, NULL, true);
    printf("Public IP Address: %s\n", rx_buffer);

    responder_close_socket(http_client);
    responder_free(http_client);
    free(rx_buffer);
    return true;
}
