/**
 * @file camera.h
 * @author Aidan (ramadan8@riseup.net)
 * @brief Prototypes for camera functions.
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#ifndef _BOX_CAMERA_H
#define _BOX_CAMERA_H

/**
 * @brief Start the camera. Must be run before capturing images.
 * 
 * @param delay Time in milliseconds to wait before returning from the function,
 *              allowing the sensor time to take in light. Defaults to 500.
 * @return true 
 * @return false 
 */
bool box_camera_init(uint16_t _delay = 500);

#endif /* _BOX_CAMERA_H */
