/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_ads1118_basic.h
 * @brief     driver ads1118 basic header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-02-28
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/02/28  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_ADS1118_BASIC_H
#define DRIVER_ADS1118_BASIC_H

#include "driver_ads1118_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ads1118_example_driver ads1118 example driver function
 * @brief    ads1118 example driver modules
 * @ingroup  ads1118_driver
 * @{
 */

/**
 * @brief ads1118 basic example default definition
 */
#define ADS1118_BASIC_DEFAULT_RANGE               ADS1118_RANGE_6P144V        /**< set range 6.144V */
#define ADS1118_BASIC_DEFAULT_RATE                ADS1118_RATE_128SPS         /**< set 128 SPS */
#define ADS1118_BASIC_DEFAULT_DOUT_PULL_UP        ADS1118_BOOL_FALSE          /**< disable dout pull up */

/**
 * @brief     basic example init
 * @param[in] mode is the adc mode
 * @param[in] channel is the adc channel
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t ads1118_basic_init(ads1118_mode_t mode, ads1118_channel_t channel);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ads1118_basic_deinit(void);

/**
 * @brief      basic example read
 * @param[out] *s points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t ads1118_basic_read(float *s);

/**
 * @brief      basic example read
 * @param[out] *deg points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t ads1118_basic_read_temperature(float *deg);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
