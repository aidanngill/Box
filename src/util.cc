/**
 * @file util.cc
 * @author Aidan (ramadan8@riseup.net)
 * @brief Implementation of basic utility functions.
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <Arduino.h>

#include "./util.h"

#include "./defs/config.h"

void box_sleep_start() {
  log_d("Entering deep sleep cycle");

  esp_sleep_enable_ext0_wakeup(BOX_INFRARED_PIN, HIGH);
  esp_deep_sleep_start();
}
