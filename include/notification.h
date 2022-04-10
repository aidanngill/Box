/**
 * @file notification.h
 * @author Aidan (ramadan8@riseup.net)
 * @brief Prototypes and enums for types of notifications for motion captured.
 * @version 0.1
 * @date 2022-04-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#ifndef _BOX_NOTIFICATION_H
#define _BOX_NOTIFICATION_H

typedef enum {
  // Ignore any motion captured.
  NOTIFICATION_NONE = 0,

  // Upload the image to the specified FTP server.
  NOTIFICATION_FTP,

  // Upload the image to a given Discord webhook.
  NOTIFICATION_DISCORD
} box_notification_t;

/**
 * @brief Upload a file to the defined FTP server.
 * 
 * @param data File buffer.
 * @param length Length of the file.
 * @param file_name Name to save the file to on the server.
 * @return void
 */
void box_notify_ftp(
  unsigned char* data,
  int length,
  const char* file_name
);

/**
 * @brief Upload a file to the Discord webhook.
 * 
 * @param buffer File buffer.
 * @param length Length of the file.
 */
void box_notify_discord(
  unsigned char* buffer,
  int length
);

#endif /* _BOX_NOTIFICATION_H */
