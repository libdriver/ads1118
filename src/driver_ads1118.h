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
 * @file      driver_ads1118.h
 * @brief     driver ads1118 header file
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

#ifndef DRIVER_ADS1118_H
#define DRIVER_ADS1118_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ads1118_driver ads1118 driver function
 * @brief    ads1118 driver modules
 * @{
 */

/**
 * @addtogroup ads1118_basic_driver
 * @{
 */

/**
 * @brief ads1118 bool enumeration definition
 */
typedef enum
{
    ADS1118_BOOL_FALSE = 0x00,        /**< disable function */
    ADS1118_BOOL_TRUE  = 0x01,        /**< enable function */
} ads1118_bool_t;

/**
 * @brief ads1118 range enumeration definition
 */
typedef enum
{
    ADS1118_RANGE_6P144V = 0x00,        /**< 6.144V range */
    ADS1118_RANGE_4P096V = 0x01,        /**< 4.096V range */
    ADS1118_RANGE_2P048V = 0x02,        /**< 2.048V range */
    ADS1118_RANGE_1P024V = 0x03,        /**< 1.024V range */
    ADS1118_RANGE_0P512V = 0x04,        /**< 0.512V range */
    ADS1118_RANGE_0P256V = 0x05,        /**< 0.256V range */
} ads1118_range_t;

/**
 * @brief ads1118 channel rate enumeration definition
 */
typedef enum
{
    ADS1118_RATE_8SPS   = 0x00,        /**< 8 sample per second */
    ADS1118_RATE_16SPS  = 0x01,        /**< 16 sample per second */
    ADS1118_RATE_32SPS  = 0x02,        /**< 32 sample per second */
    ADS1118_RATE_64SPS  = 0x03,        /**< 64 sample per second */
    ADS1118_RATE_128SPS = 0x04,        /**< 128 sample per second */
    ADS1118_RATE_250SPS = 0x05,        /**< 250 sample per second */
    ADS1118_RATE_475SPS = 0x06,        /**< 475 sample per second */
    ADS1118_RATE_860SPS = 0x07,        /**< 860 sample per second */
} ads1118_rate_t;

/**
 * @brief ads1118 channel enumeration definition
 */
typedef enum
{
    ADS1118_CHANNEL_AIN0_AIN1 = 0x00,        /**< AIN0 and AIN1 pins */
    ADS1118_CHANNEL_AIN0_AIN3 = 0x01,        /**< AIN0 and AIN3 pins */
    ADS1118_CHANNEL_AIN1_AIN3 = 0x02,        /**< AIN1 and AIN3 pins */
    ADS1118_CHANNEL_AIN2_AIN3 = 0x03,        /**< AIN2 and AIN3 pins */
    ADS1118_CHANNEL_AIN0_GND  = 0x04,        /**< AIN0 and GND pins */
    ADS1118_CHANNEL_AIN1_GND  = 0x05,        /**< AIN1 and GND pins */
    ADS1118_CHANNEL_AIN2_GND  = 0x06,        /**< AIN2 and GND pins */
    ADS1118_CHANNEL_AIN3_GND  = 0x07,        /**< AIN3 and GND pins */
} ads1118_channel_t;

/**
 * @brief ads1118 mode enumeration definition
 */
typedef enum
{
    ADS1118_MODE_ADC         = 0x00,        /**< adc mode */
    ADS1118_MODE_TEMPERATURE = 0x01,        /**< temperature mode */
} ads1118_mode_t;

/**
 * @brief ads1118 handle structure definition
 */
typedef struct ads1118_handle_s
{
    uint8_t (*spi_init)(void);                                              /**< point to a spi_init function address */
    uint8_t (*spi_deinit)(void);                                            /**< point to a spi_deinit function address */
    uint8_t (*spi_transmit)(uint8_t *tx, uint8_t *rx, uint16_t len);        /**< point to a spi_transmit function address */
    void (*delay_ms)(uint32_t ms);                                          /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                        /**< point to a debug_print function address */
    uint8_t inited;                                                         /**< inited flag */
} ads1118_handle_t;

/**
 * @brief ads1118 information structure definition
 */
typedef struct ads1118_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} ads1118_info_t;

/**
 * @}
 */

/**
 * @defgroup ads1118_link_driver ads1118 link driver function
 * @brief    ads1118 link driver modules
 * @ingroup  ads1118_driver
 * @{
 */

/**
 * @brief     initialize ads1118_handle_t structure
 * @param[in] HANDLE points to an ads1118 handle structure
 * @param[in] STRUCTURE is ads1118_handle_t
 * @note      none
 */
#define DRIVER_ADS1118_LINK_INIT(HANDLE, STRUCTURE)             memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link spi_init function
 * @param[in] HANDLE points to an ads1118 handle structure
 * @param[in] FUC points to an spi_init function address
 * @note      none
 */
#define DRIVER_ADS1118_LINK_SPI_INIT(HANDLE, FUC)               (HANDLE)->spi_init = FUC

/**
 * @brief     link spi_deinit function
 * @param[in] HANDLE points to an ads1118 handle structure
 * @param[in] FUC points to an spi_deinit function address
 * @note      none
 */
#define DRIVER_ADS1118_LINK_SPI_DEINIT(HANDLE, FUC)             (HANDLE)->spi_deinit = FUC

/**
 * @brief     link spi_transmit function
 * @param[in] HANDLE points to an ads1118 handle structure
 * @param[in] FUC points to an spi_transmit function address
 * @note      none
 */
#define DRIVER_ADS1118_LINK_SPI_TRANSMIT(HANDLE, FUC)           (HANDLE)->spi_transmit = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an ads1118 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_ADS1118_LINK_DELAY_MS(HANDLE, FUC)               (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an ads1118 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_ADS1118_LINK_DEBUG_PRINT(HANDLE, FUC)            (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup ads1118_basic_driver ads1118 basic driver function
 * @brief    ads1118 basic driver modules
 * @ingroup  ads1118_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an ads1118 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ads1118_info(ads1118_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an ads1118 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t ads1118_init(ads1118_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an ads1118 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 spi deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t ads1118_deinit(ads1118_handle_t *handle);

/**
 * @brief      read data from the chip once
 * @param[in]  *handle points to an ads1118 handle structure
 * @param[out] *raw points to a raw adc buffer
 * @param[out] *v points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 single read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ads1118_single_read(ads1118_handle_t *handle, int16_t *raw, float *v);

/**
 * @brief      read data from the chip continuously
 * @param[in]  *handle points to an ads1118 handle structure
 * @param[out] *raw points to a raw adc buffer
 * @param[out] *v points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 continuous read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       this function can be used only after run ads1118_start_continuous_read
 *             and can be stopped by ads1118_stop_continuous_read
 */
uint8_t ads1118_continuous_read(ads1118_handle_t *handle, int16_t *raw, float *v);

/**
 * @brief     start the chip reading
 * @param[in] *handle points to an ads1118 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 start continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ads1118_start_continuous_read(ads1118_handle_t *handle);

/**
 * @brief     stop the chip reading
 * @param[in] *handle points to an ads1118 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ads1118_stop_continuous_read(ads1118_handle_t *handle);

/**
 * @brief      temperature convert
 * @param[in]  *handle points to an ads1118 handle structure
 * @param[in]  raw is the adc raw data
 * @param[out] *deg points to a deg buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ads1118_temperature_convert(ads1118_handle_t *handle, int16_t raw, float *deg);

/**
 * @brief     set the adc channel
 * @param[in] *handle points to an ads1118 handle structure
 * @param[in] channel is the adc channel
 * @return    status code
 *            - 0 success
 *            - 1 set channel failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ads1118_set_channel(ads1118_handle_t *handle, ads1118_channel_t channel);

/**
 * @brief      get the adc channel
 * @param[in]  *handle points to an ads1118 handle structure
 * @param[out] *channel points to a channel buffer
 * @return     status code
 *             - 0 success
 *             - 1 get channel failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ads1118_get_channel(ads1118_handle_t *handle, ads1118_channel_t *channel);

/**
 * @brief     set the adc range
 * @param[in] *handle points to an ads1118 handle structure
 * @param[in] range is the adc max voltage range
 * @return    status code
 *            - 0 success
 *            - 1 set range failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ads1118_set_range(ads1118_handle_t *handle, ads1118_range_t range);

/**
 * @brief      get the adc range
 * @param[in]  *handle points to an ads1118 handle structure
 * @param[out] *range points to a voltage range buffer
 * @return     status code
 *             - 0 success
 *             - 1 get range failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ads1118_get_range(ads1118_handle_t *handle, ads1118_range_t *range);

/**
 * @brief     set the sample rate
 * @param[in] *handle points to an ads1118 handle structure
 * @param[in] rate is the adc sample rate
 * @return    status code
 *            - 0 success
 *            - 1 set rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ads1118_set_rate(ads1118_handle_t *handle, ads1118_rate_t rate);

/**
 * @brief      get the sample rate
 * @param[in]  *handle points to an ads1118 handle structure
 * @param[out] *rate points to an adc sample rate buffer
 * @return     status code
 *             - 0 success
 *             - 1 get rate failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ads1118_get_rate(ads1118_handle_t *handle, ads1118_rate_t *rate);

/**
 * @brief     set the chip mode
 * @param[in] *handle points to an ads1118 handle structure
 * @param[in] mode is the chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ads1118_set_mode(ads1118_handle_t *handle, ads1118_mode_t mode);

/**
 * @brief      get the chip mode
 * @param[in]  *handle points to an ads1118 handle structure
 * @param[out] *mode points to a mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ads1118_get_mode(ads1118_handle_t *handle, ads1118_mode_t *mode);

/**
 * @brief     enable or disable dout pull up
 * @param[in] *handle points to an ads1118 handle structure
 * @param[in] enable is a bool value
 * @return    status code
 *            - 0 success
 *            - 1 set dout pull up failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ads1118_set_dout_pull_up(ads1118_handle_t *handle, ads1118_bool_t enable);

/**
 * @brief      get dout pull up status
 * @param[in]  *handle points to an ads1118 handle structure
 * @param[out] *enable points to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get dout pull up failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ads1118_get_dout_pull_up(ads1118_handle_t *handle, ads1118_bool_t *enable);

/**
 * @}
 */

/**
 * @defgroup ads1118_extern_driver ads1118 extern driver function
 * @brief    ads1118 extern driver modules
 * @ingroup  ads1118_driver
 * @{
 */

/**
 * @brief      chip transmit
 * @param[in]  *handle points to an ads1118 handle structure
 * @param[in]  *tx points to a tx buffer
 * @param[out] *rx points to a rx buffer
 * @param[in]  len is the tx and rx buffer
 * @return     status code
 *             - 0 success
 *             - 1 transmit failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ads1118_transmit(ads1118_handle_t *handle, uint8_t *tx, uint8_t *rx, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
