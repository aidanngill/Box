/**
 * @file net.h
 * @author Aidan (ramadan8@riseup.net)
 * @brief Prototypes for networking functions, including WiFi and FTP.
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#ifndef _BOX_NET_H
#define _BOX_NET_H

/**
 * @brief Initialize the WiFi and NTP connection.
 * 
 * @param ssid Name of the WiFi network.
 * @param password Password to log in to the WiFi network.
 * @return true 
 * @return false 
 */
bool box_wifi_init(const char* ssid, const char* password);

/**
 * @brief Cleanly disconnect from the WiFi connection.
 * @return void
 */
void box_wifi_disconnect();

#endif /* _BOX_NET_H */
