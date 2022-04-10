/**
 * @file notification.cc
 * @author Aidan (ramadan8@riseup.net)
 * @brief Implementation of the notification functions.
 * @version 0.1
 * @date 2022-04-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <ESP32_FTPClient.h>

#include "./notification.h"

#include "./defs/config.h"

ESP32_FTPClient BoxFTP(
  BOX_FTP_HOST,
  BOX_FTP_PORT,
  BOX_FTP_USER,
  BOX_FTP_PASS
);

void box_notify_ftp(
  unsigned char* data,
  int length,
  const char* file_name
) {
  BoxFTP.OpenConnection();
  BoxFTP.InitFile("Type I");
  BoxFTP.ChangeWorkDir("/srv/ftp/box");
  BoxFTP.NewFile(file_name);
  BoxFTP.WriteData(data, length);
  BoxFTP.CloseFile();

  log_d(
    "Successfully uploaded %d bytes to '%s' on the FTP server",
    length, file_name
  );
}

// DigiCert Root CA.
const char* discord_root_ca = \
  "-----BEGIN CERTIFICATE-----\n" \
  "MIIDdzCCAl+gAwIBAgIEAgAAuTANBgkqhkiG9w0BAQUFADBaMQswCQYDVQQGEwJJ\n" \
  "RTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJlclRydXN0MSIwIAYD\n" \
  "VQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTAwMDUxMjE4NDYwMFoX\n" \
  "DTI1MDUxMjIzNTkwMFowWjELMAkGA1UEBhMCSUUxEjAQBgNVBAoTCUJhbHRpbW9y\n" \
  "ZTETMBEGA1UECxMKQ3liZXJUcnVzdDEiMCAGA1UEAxMZQmFsdGltb3JlIEN5YmVy\n" \
  "VHJ1c3QgUm9vdDCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKMEuyKr\n" \
  "mD1X6CZymrV51Cni4eiVgLGw41uOKymaZN+hXe2wCQVt2yguzmKiYv60iNoS6zjr\n" \
  "IZ3AQSsBUnuId9Mcj8e6uYi1agnnc+gRQKfRzMpijS3ljwumUNKoUMMo6vWrJYeK\n" \
  "mpYcqWe4PwzV9/lSEy/CG9VwcPCPwBLKBsua4dnKM3p31vjsufFoREJIE9LAwqSu\n" \
  "XmD+tqYF/LTdB1kC1FkYmGP1pWPgkAx9XbIGevOF6uvUA65ehD5f/xXtabz5OTZy\n" \
  "dc93Uk3zyZAsuT3lySNTPx8kmCFcB5kpvcY67Oduhjprl3RjM71oGDHweI12v/ye\n" \
  "jl0qhqdNkNwnGjkCAwEAAaNFMEMwHQYDVR0OBBYEFOWdWTCCR1jMrPoIVDaGezq1\n" \
  "BE3wMBIGA1UdEwEB/wQIMAYBAf8CAQMwDgYDVR0PAQH/BAQDAgEGMA0GCSqGSIb3\n" \
  "DQEBBQUAA4IBAQCFDF2O5G9RaEIFoN27TyclhAO992T9Ldcw46QQF+vaKSm2eT92\n" \
  "9hkTI7gQCvlYpNRhcL0EYWoSihfVCr3FvDB81ukMJY2GQE/szKN+OMY3EU/t3Wgx\n" \
  "jkzSswF07r51XgdIGn9w/xZchMB5hbgF/X++ZRGjD8ACtPhSNzkE1akxehi/oCr0\n" \
  "Epn3o0WC4zxe9Z2etciefC7IpJ5OCBRLbf1wbWsaY71k5h+3zvDyny67G7fyUIhz\n" \
  "ksLi4xaNmjICq44Y3ekQEe5+NauQrz4wlHrQMz2nZQ/1/I6eYs9HRCwBXbsdtTLS\n" \
  "R9I4LtD+gdwyah617jzV/OeBHRnDJELqYzmp\n" \
  "-----END CERTIFICATE-----\n" \
  "\n";

void box_notify_discord(
  unsigned char* buffer,
  int length
) {
  WiFiClientSecure client;
  client.setCACert(discord_root_ca);

  if (client.connect("discord.com", 443)) {
    // TODO: Investigate why this is needed.
    String mf_item_one = "--boxnetdiscord\r\n";
    mf_item_one += "Content-Disposition: form-data; name=\"boxnetdiscord\"\r\n\r\n";
    mf_item_one += String(1) + "\r\n";

    String mf_head = "--boxnetdiscord\r\n";
    mf_head += "Content-Disposition: form-data; name=\"file\";filename=\"file.jpg\"\r\n";
    mf_head += "Content-Type: image/jpeg\r\n\r\n";

    String mf_tail = "\r\n--boxnetdiscord--\r\n";

    // Construct the path to the webhook.
    client.print("POST https://discord.com/api/webhooks/");
    client.print(BOX_DISCORD_ID); // TODO: Don't hardcode from macros, use params.
    client.print("/");
    client.print(BOX_DISCORD_SECRET);
    client.println(" HTTP/1.1");
    client.println("Host: discord.com");

    uint32_t mf_content_length = length;
    mf_content_length += mf_item_one.length();
    mf_content_length += mf_head.length();
    mf_content_length += mf_tail.length();

    client.println("Content-Length: " + String(mf_content_length));
    client.println("Content-Type: multipart/form-data; boundary=boxnetdiscord");
    client.println();
    client.print(mf_item_one);
    client.println();
    client.print(mf_head);

    // Write the image's contents in 1024 bytes at a time.
    for (size_t n = 0; n < length; n = n + 1024) {
      if (n + 1024 < length) {
        client.write(buffer, 1024);
        buffer += 1024;
      } else if (length % 1024 > 0) {
        size_t remainder = length % 1024;
        client.write(buffer, remainder);
      }
    }

    client.print(mf_tail);

    delay(500); // TODO: Find reason we have to wait a bit before closing.

    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }

    client.stop();

    log_d("Successfully posted an image on Discord");
  }
}
