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
 * @file      driver_ads1118_read_test.c
 * @brief     driver ads1118 read test source file
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

#include "driver_ads1118_read_test.h"

static ads1118_handle_t gs_handle;        /**< ads1118 handle */

/**
 * @brief     read test
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t ads1118_read_test(uint32_t times)
{
    uint8_t res;
    uint8_t i;
    ads1118_info_t info;
    
    /* link interface function */
    DRIVER_ADS1118_LINK_INIT(&gs_handle, ads1118_handle_t); 
    DRIVER_ADS1118_LINK_SPI_INIT(&gs_handle, ads1118_interface_spi_init);
    DRIVER_ADS1118_LINK_SPI_DEINIT(&gs_handle, ads1118_interface_spi_deinit);
    DRIVER_ADS1118_LINK_SPI_TRANSMIT(&gs_handle, ads1118_interface_spi_transmit);
    DRIVER_ADS1118_LINK_DELAY_MS(&gs_handle, ads1118_interface_delay_ms);
    DRIVER_ADS1118_LINK_DEBUG_PRINT(&gs_handle, ads1118_interface_debug_print);
    
    /* get information */
    res = ads1118_info(&info);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        ads1118_interface_debug_print("ads1118: chip is %s.\n", info.chip_name);
        ads1118_interface_debug_print("ads1118: manufacturer is %s.\n", info.manufacturer_name);
        ads1118_interface_debug_print("ads1118: interface is %s.\n", info.interface);
        ads1118_interface_debug_print("ads1118: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ads1118_interface_debug_print("ads1118: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ads1118_interface_debug_print("ads1118: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ads1118_interface_debug_print("ads1118: max current is %0.2fmA.\n", info.max_current_ma);
        ads1118_interface_debug_print("ads1118: max temperature is %0.1fC.\n", info.temperature_max);
        ads1118_interface_debug_print("ads1118: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* ads1118 init */
    res = ads1118_init(&gs_handle);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: init failed.\n");
        
        return 1;
    }
    
    /* set channel AIN0 GND */
    res = ads1118_set_channel(&gs_handle, ADS1118_CHANNEL_AIN0_GND);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set range 6.144V */
    res = ads1118_set_range(&gs_handle, ADS1118_RANGE_6P144V);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set 128sps rate */
    res = ads1118_set_rate(&gs_handle, ADS1118_RATE_128SPS);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable dout pull up */
    res = ads1118_set_dout_pull_up(&gs_handle, ADS1118_BOOL_FALSE);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set dout pull up failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set adc mode */
    res = ads1118_set_mode(&gs_handle, ADS1118_MODE_ADC);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set mode failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    
    /* start read test */
    ads1118_interface_debug_print("ads1118: start read test.\n");
    
    /* AIN0 to GND */
    ads1118_interface_debug_print("ads1118: AIN0 to GND.\n");
    
    /* start continuous read */
    ads1118_interface_debug_print("ads1118: continuous read test.\n");
    res = ads1118_start_continuous_read(&gs_handle);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: start continues read mode failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    
    /* delay 100 ms */
    ads1118_interface_delay_ms(100);
    for (i = 0; i < times; i++)
    {
        int16_t raw;
        float s;
      
        /* continuous read */
        res = ads1118_continuous_read(&gs_handle, (int16_t *)&raw, (float *)&s);
        if (res != 0)
        {
            ads1118_interface_debug_print("ads1118: read failed.\n");
            (void)ads1118_deinit(&gs_handle);
            
            return 1;
        }
        ads1118_interface_debug_print("ads1118: %d continues mode %0.3fV.\n", i+1, s);
        ads1118_interface_delay_ms(1000);
    }
    
    /* stop continuous read */
    res = ads1118_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: stop continues read mode failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    
    /* start single read */
    ads1118_interface_debug_print("ads1118: single read test.\n");
    for (i = 0; i < times; i++)
    {
        int16_t raw;
        float s;
     
        /* single read */
        res = ads1118_single_read(&gs_handle, (int16_t *)&raw, (float *)&s);
        if (res != 0)
        {
            ads1118_interface_debug_print("ads1118: read failed.\n");
            (void)ads1118_deinit(&gs_handle);
            
            return 1;
        }
        ads1118_interface_debug_print("ads1118: %d single mode %0.3fV.\n", i+1, s);
        ads1118_interface_delay_ms(1000);
    }
    
    /* set temperature mode */
    res = ads1118_set_mode(&gs_handle, ADS1118_MODE_TEMPERATURE);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set mode failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    
    /* temperature read test */
    ads1118_interface_debug_print("ads1118: temperature read test.\n");
    for (i = 0; i < times; i++)
    {
        int16_t raw;
        float s;
     
        /* single read */
        res = ads1118_single_read(&gs_handle, (int16_t *)&raw, (float *)&s);
        if (res != 0)
        {
            ads1118_interface_debug_print("ads1118: read failed.\n");
            (void)ads1118_deinit(&gs_handle);
            
            return 1;
        }
        res = ads1118_temperature_convert(&gs_handle, raw, &s);
        if (res != 0)
        {
            ads1118_interface_debug_print("ads1118: temperature convert failed.\n");
            (void)ads1118_deinit(&gs_handle);
            
            return 1;
        }
        ads1118_interface_debug_print("ads1118: %d temperature is %0.3fC.\n", i + 1, s);
        ads1118_interface_delay_ms(1000);
    }
    
    /* finish read test */
    ads1118_interface_debug_print("ads1118: finish read test.\n");
    (void)ads1118_deinit(&gs_handle);
    
    return 0;
}
