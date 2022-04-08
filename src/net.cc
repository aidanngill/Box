/**
 * @file net.cc
 * @author Aidan (ramadan8@riseup.net)
 * @brief Implementation of the networking functions.
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <WiFi.h>
#include <ESP32_FTPClient.h>

#include "./net.h"

#include "./defs/config.h"

ESP32_FTPClient BoxFTP(
  BOX_FTP_HOST,
  BOX_FTP_PORT,
  BOX_FTP_USER,
  BOX_FTP_PASS
);

bool box_wifi_init(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) delay(100);

  configTime(
    BOX_TIME_OFFSET * 60 * 60,
    BOX_TIME_DST_OFFSET,
    "pool.ntp.org"
  );

  return true;
}

void box_wifi_disconnect() {
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void box_ftp_upload(
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
