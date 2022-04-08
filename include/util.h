/**
 * @file util.h
 * @author Aidan (ramadan8@riseup.net)
 * @brief Prototypes for basic utility functions.
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#ifndef _BOX_UTIL_H
#define _BOX_UTIL_H

/**
 * @brief Enter the ESP32's deep sleep mode for lowered power consumption.
 * 
 * The infrared pin will also be assigned as a wakeup pin, meaning that it can
 * wake the ESP32 out of the sleep to do the camera function over again.
 * 
 * The use of some GPIO pins may cause interference with other features of the
 * ESP32, such as 12/13 interfering with the SD card functionality.
 * 
 * @return void
 */
void box_sleep_start();

#endif /* _BOX_UTIL_H */
