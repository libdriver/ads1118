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
 * @file      driver_ads1118_shot.c
 * @brief     driver ads1118 shot source file
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

#include "driver_ads1118_shot.h"

static ads1118_handle_t gs_handle;        /**< ads1118 handle */

/**
 * @brief     shot example init
 * @param[in] mode is the adc mode
 * @param[in] channel is the adc channel
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t ads1118_shot_init(ads1118_mode_t mode, ads1118_channel_t channel)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_ADS1118_LINK_INIT(&gs_handle, ads1118_handle_t); 
    DRIVER_ADS1118_LINK_SPI_INIT(&gs_handle, ads1118_interface_spi_init);
    DRIVER_ADS1118_LINK_SPI_DEINIT(&gs_handle, ads1118_interface_spi_deinit);
    DRIVER_ADS1118_LINK_SPI_TRANSMIT(&gs_handle, ads1118_interface_spi_transmit);
    DRIVER_ADS1118_LINK_DELAY_MS(&gs_handle, ads1118_interface_delay_ms);
    DRIVER_ADS1118_LINK_DEBUG_PRINT(&gs_handle, ads1118_interface_debug_print);
    
    /* ads1118 init */
    res = ads1118_init(&gs_handle);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: init failed.\n");
        
        return 1;
    }
    
    /* set channel */
    res = ads1118_set_channel(&gs_handle, channel);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default range */
    res = ads1118_set_range(&gs_handle, ADS1118_SHOT_DEFAULT_RANGE);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default rate */
    res = ads1118_set_rate(&gs_handle, ADS1118_SHOT_DEFAULT_RATE);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set adc mode */
    res = ads1118_set_mode(&gs_handle, mode);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set mode failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default dout pull up */
    res = ads1118_set_dout_pull_up(&gs_handle, ADS1118_SHOT_DEFAULT_DOUT_PULL_UP);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set dout pull up failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }

    return 0;
}

/**
 * @brief      shot example read
 * @param[out] *s points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t ads1118_shot_read(float *s)
{
    int16_t raw;
  
    /* read data */
    if (ads1118_single_read(&gs_handle, (int16_t *)&raw, s) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      shot example read
 * @param[out] *deg points to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t ads1118_shot_read_temperature(float *deg)
{
    int16_t raw;
  
    /* read data */
    if (ads1118_single_read(&gs_handle, (int16_t *)&raw, deg) != 0)
    {
        return 1;
    }
    
    /* temperature convert */
    if (ads1118_temperature_convert(&gs_handle, raw, deg) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  shot example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ads1118_shot_deinit(void)
{
    uint8_t res;
    
    /* deinit ads1118 */
    res = ads1118_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}
