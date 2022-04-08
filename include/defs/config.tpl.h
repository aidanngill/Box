/**
 * @file config.h
 * @author Aidan (ramadan8@riseup.net)
 * @brief Variables to configure the project to your needs.
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Pin to use for the PIR sensor.
#define BOX_INFRARED_PIN GPIO_NUM_13

// Timezone offset to use. In this case it is UTC+0.
#define BOX_TIME_OFFSET 0

// 3600 if using daylight savings time, 0 otherwise.
#define BOX_TIME_DST_OFFSET 0

// WiFi SSID/name.
#define BOX_WIFI_SSID "your-wifi-ssid"

// WiFi password.
#define BOX_WIFI_PASS "your-wifi-password"

// FTP server information.
#define BOX_FTP_HOST "your-ftp-host.com"
#define BOX_FTP_PORT 21
#define BOX_FTP_USER "your-ftp-username"
#define BOX_FTP_PASS "y0ur-f7p-p455w0rd"

// Define to enable serial logging.
#define BOX_DEBUG_MODE

//#define CAMERA_MODEL_WROVER_KIT // Has PSRAM
//#define CAMERA_MODEL_ESP_EYE // Has PSRAM
//#define CAMERA_MODEL_M5STACK_PSRAM // Has PSRAM
//#define CAMERA_MODEL_M5STACK_V2_PSRAM // M5Camera version B Has PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE // Has PSRAM
//#define CAMERA_MODEL_M5STACK_ESP32CAM // No PSRAM
#define CAMERA_MODEL_AI_THINKER // Has PSRAM
//#define CAMERA_MODEL_TTGO_T_JOURNAL // No PSRAM
