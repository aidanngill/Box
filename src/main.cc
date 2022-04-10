/**
 * @file main.cc
 * @author Aidan (ramadan8@riseup.net)
 * @brief Main functions wherein the logic of the project will run.
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <Arduino.h>
#include <esp_camera.h>
#include <time.h>

#include "./camera.h"
#include "./net.h"
#include "./notification.h"
#include "./util.h"

#include "./defs/config.h"

void box_setup() {
#ifdef BOX_DEBUG_MODE
  Serial.begin(115200);
  Serial.setDebugOutput(true);
#endif

  log_v("Initialized the serial logger");

  // If a reset is triggered by a brownout or from the reset button itself,
  // then we instantly go to sleep to skip out on potentially causing another
  // brownout from power heavy functions like WiFi initialization.
  if (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_EXT0
   || digitalRead(BOX_INFRARED_PIN) == LOW) {
    log_d("Wakeup was not caused by GPIO, exiting");
    return;
  }

  if (BOX_NOTIFICATION_TYPE == NOTIFICATION_NONE) {
    log_d("Notifications are not configured");
    return;
  }

  if (!box_camera_init()) {
    log_e("Failed to initialize the camera");
    return;
  }

  // Start by capturing the image before any time and energy consuming
  // processes, such as connecting to the WiFi.
  camera_fb_t* fb = NULL;
  fb = esp_camera_fb_get();

  if (!fb) {
    log_e("Failed to get the frame buffer");
    return;
  }

  log_d("Successfully captured an image");

  if (box_wifi_init(BOX_WIFI_SSID, BOX_WIFI_PASS)) {
    log_d("Successfully connected to the WiFi");

    // Our time string format will only ever be 22 characters long.
    struct tm time_info;
    char time_string_buffer[22] = "latest.jpg";

    if (getLocalTime(&time_info)) {
      strftime(
        time_string_buffer,
        sizeof(time_string_buffer),
        "%Y%m%d%H%M%S_%L.jpg",
        &time_info
      );
    }

    switch (BOX_NOTIFICATION_TYPE) {
      case NOTIFICATION_DISCORD: {
        box_notify_discord(fb->buf, fb->len);
      } break;
      case NOTIFICATION_FTP: {
        box_notify_ftp(fb->buf, fb->len, time_string_buffer);
      } break;
      default: {
        log_w("Unknown notification type specified");
        break;
      }
    }

    box_wifi_disconnect();
  } else {
    log_e("Failed to initialize WiFi");
  }

  esp_camera_fb_return(fb);
}

void setup() {
  box_setup();
  box_sleep_start();
}

void loop() {}
