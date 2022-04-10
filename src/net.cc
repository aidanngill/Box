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

#include "./net.h"

#include "./defs/config.h"

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
