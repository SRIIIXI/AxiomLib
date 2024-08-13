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
#include "ResponderSsl.h"
#include "Dictionary.h"

#include <memory.h>

typedef struct smtp_t
{
    char host[33];
    char username[33];
    char password[33];
    uint16_t port;
    bool start_tls;
    const char* public_ip_address;
    SecurityType securityType;
    char errorStr[65];
    dictionary_t* email_header;
    mail_body_t* email_body;
    responder_ssl_t* bearer;
}smtp_t;

//SmtpClient::SmtpClient()
//{
//	host = "";
//	username = "";
//	password = "";
//	port = 25;
//	securityType = None;
//	startTls = false;
//}

//SmtpClient::SmtpClient(const std::string hoststr, uint16_t portstr, std::string usernamestr, std::string passwordstr, SecurityType sectype)
//{
//	host = hoststr;
//	username = usernamestr;
//	password = passwordstr;
//	port = portstr;
//	securityType = sectype;
//	startTls = false;
//}

//SmtpClient::~SmtpClient()
//{
//	bearer.CloseSocket();
//}

smtp_t* smtp_allocate(void)
{
    return NULL;
}

void smtp_free(smtp_t* ptr)
{
    return;
}



void smtp_set_account_information(smtp_t* ptr, const char* hoststr, uint16_t portstr, const char* usernamestr, const char* passwordstr, SecurityType sectype)
{
//	host = hoststr;
//	username = usernamestr;
//	password = passwordstr;
//	port = portstr;
//	securityType = sectype;
//	startTls = false;

    return;
}

bool smtp_connect(smtp_t* ptr)
{
//	bool need_ssl = false;

//	// Note: For SMTP TLS sessions starts on plain sockets and switches to SSL sockets after STARTTLS negotiation
//	if (securityType == None || securityType == Tls)
//	{
//		need_ssl = false;
//	}
//	else
//	{
//		need_ssl = true;
//	}

//    int retcode;

//    if (bearer.CreateSocket(host.c_str(), port, need_ssl))
//    {
//        if (bearer.ConnectSocket(retcode))
//        {
//			std::string resp;
//			bearer.ReceiveString(resp);
//            return true;
//        }
//    }

    return false;
}

bool smtp_disconnect(smtp_t* ptr)
{
//	if (bearer.IsConnected())
//	{
//		return bearer.CloseSocket();
//	}

	return false;
}

bool smtp_send_helo(smtp_t* ptr)
{
//    std::string resp;
//    char buff[128] = { 0 };
//    sprintf(buff, "EHLO %s\r\n", publicIp.c_str());

//    std::string helo = buff;
//    bearer.SendString(helo);

//    while (true)
//    {
//		if (!bearer.ReceiveString(resp))
//		{
//		    return false;
//		}

//		if (strcontains(resp.c_str(), "STARTTLS"))
//		{
//			startTls = true;
//		}

//        if(bearer.PendingPreFetchedBufferSize() < 1)
//        {
//            return true;
//        }
//    }

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
    return false;
    //return startTls;
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
//	std::string resp;
//	std::vector<std::string> tokens;

//	char buff[128] = { 0 };

//	sprintf(buff, "QUIT\r\n");
//	int len = (int)strlen(buff);

//	bearer.SendString(buff);

//	while (true)
//	{
//		if (!bearer.ReceiveString(resp))
//		{
//			return false;
//		}

//		if (strcontains(resp.c_str(), "221"))
//		{
//			break;
//		}
//	}

	return true;
}
