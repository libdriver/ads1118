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
 * @file      driver_ads1118_register_test.c
 * @brief     driver ads1118 register test source file
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
 
#include "driver_ads1118_register_test.h"
#include <stdlib.h>

static ads1118_handle_t gs_handle;        /**< ads1118 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t ads1118_register_test(void)
{
    uint8_t res;
    ads1118_info_t info;
    ads1118_channel_t channel;
    ads1118_range_t range;
    ads1118_rate_t rate;
    ads1118_bool_t enable;
    ads1118_mode_t mode;

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
    
    /* start register test */
    ads1118_interface_debug_print("ads1118: start register test.\n");
    
    /* ads1118 init */
    res = ads1118_init(&gs_handle);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: init failed.\n");
        
        return 1;
    }
    
    /* ads1118_set_channel/ads1118_get_channel test */
    ads1118_interface_debug_print("ads1118: ads1118_set_channel/ads1118_get_channel test.\n");
    
    /* AIN0 to GND */
    res = ads1118_set_channel(&gs_handle, ADS1118_CHANNEL_AIN0_GND);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set channel ain0_ground.\n");
    res = ads1118_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check channel %s.\n", channel == ADS1118_CHANNEL_AIN0_GND ? "ok" : "error");
    
    /* AIN1 to GND */
    res = ads1118_set_channel(&gs_handle, ADS1118_CHANNEL_AIN1_GND);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set channel ain1_ground.\n");
    res = ads1118_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check channel %s.\n", channel == ADS1118_CHANNEL_AIN1_GND ? "ok" : "error");
    
    /* AIN2 to GND */
    res = ads1118_set_channel(&gs_handle, ADS1118_CHANNEL_AIN2_GND);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set channel ain2_ground.\n");
    res = ads1118_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check channel %s.\n", channel == ADS1118_CHANNEL_AIN2_GND ? "ok" : "error");
    
    /* AIN3 to GND */
    res = ads1118_set_channel(&gs_handle, ADS1118_CHANNEL_AIN3_GND);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set channel ain3_ground.\n");
    res = ads1118_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check channel %s.\n", channel == ADS1118_CHANNEL_AIN3_GND ? "ok" : "error");
    
    /* AIN0 to AIN1 */
    res = ads1118_set_channel(&gs_handle, ADS1118_CHANNEL_AIN0_AIN1);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set channel ain0_ain1.\n");
    res = ads1118_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check channel %s.\n", channel == ADS1118_CHANNEL_AIN0_AIN1 ? "ok" : "error");
    
    /* AIN0 to AIN3 */
    res = ads1118_set_channel(&gs_handle, ADS1118_CHANNEL_AIN0_AIN3);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set channel ain0_ain3.\n");
    res = ads1118_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check channel %s.\n", channel == ADS1118_CHANNEL_AIN0_AIN3 ? "ok" : "error");
    
    /* AIN1 to AIN3 */
    res = ads1118_set_channel(&gs_handle, ADS1118_CHANNEL_AIN1_AIN3);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set channel ain1_ain3.\n");
    res = ads1118_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check channel %s.\n", channel == ADS1118_CHANNEL_AIN1_AIN3 ? "ok" : "error");
    
    /* AIN2 to AIN3 */
    res = ads1118_set_channel(&gs_handle, ADS1118_CHANNEL_AIN2_AIN3);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set channel ain2_ain3.\n");
    res = ads1118_get_channel(&gs_handle, &channel);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get channel failed.\n");
        (void)ads1118_deinit(&gs_handle);
       
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check channel %s.\n", channel == ADS1118_CHANNEL_AIN2_AIN3 ? "ok" : "error");
    
    /* ads1118_set_range/ads1118_get_range test */
    ads1118_interface_debug_print("ads1118: ads1118_set_range/ads1118_get_range test.\n");
    
    /* set 6.144V */
    res = ads1118_set_range(&gs_handle, ADS1118_RANGE_6P144V);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set range 6.144V.\n");
    res = ads1118_get_range(&gs_handle, &range);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check range %s.\n", range == ADS1118_RANGE_6P144V ? "ok" : "error");
    
    /* set 4.096V */
    res = ads1118_set_range(&gs_handle, ADS1118_RANGE_4P096V);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set range 4.096V.\n");
    res = ads1118_get_range(&gs_handle, &range);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check range %s.\n", range == ADS1118_RANGE_4P096V ? "ok" : "error");
    
    /* set 2.048V */
    res = ads1118_set_range(&gs_handle, ADS1118_RANGE_2P048V);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set range 2.048V.\n");
    res = ads1118_get_range(&gs_handle, &range);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check range %s.\n", range == ADS1118_RANGE_2P048V ? "ok" : "error");
    
    /* set 1.024V */
    res = ads1118_set_range(&gs_handle, ADS1118_RANGE_1P024V);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set range 1.024V.\n");
    res = ads1118_get_range(&gs_handle, &range);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check range %s.\n", range == ADS1118_RANGE_1P024V ? "ok" : "error");
    
    /* set 0.512V */
    res = ads1118_set_range(&gs_handle, ADS1118_RANGE_0P512V);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set range 0.512V.\n");
    res = ads1118_get_range(&gs_handle, &range);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check range %s.\n", range == ADS1118_RANGE_0P512V ? "ok" : "error");
    
    /* set 0.256V */
    res = ads1118_set_range(&gs_handle, ADS1118_RANGE_0P256V);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set range 0.256V.\n");
    res = ads1118_get_range(&gs_handle, &range);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get range failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check range %s.\n", range == ADS1118_RANGE_0P256V ? "ok" : "error");
    
    /* ads1118_set_mode/ads1118_get_mode test */
    ads1118_interface_debug_print("ads1118: ads1118_set_mode/ads1118_get_mode test.\n");
    
    /* set adc mode */
    res = ads1118_set_mode(&gs_handle, ADS1118_MODE_ADC);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set mode failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set adc mode.\n");
    res = ads1118_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get mode failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check mode %s.\n", mode == ADS1118_MODE_ADC ? "ok" : "error");
    
    /* set temperature mode */
    res = ads1118_set_mode(&gs_handle, ADS1118_MODE_TEMPERATURE);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set mode failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set temperature mode.\n");
    res = ads1118_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get mode failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check mode %s.\n", mode == ADS1118_MODE_TEMPERATURE ? "ok" : "error");
    
    /* ads1118_set_rate/ads1118_get_rate test */
    ads1118_interface_debug_print("ads1118: ads1118_set_rate/ads1118_get_rate test.\n");
    
    /* set 8SPS */
    res = ads1118_set_rate(&gs_handle, ADS1118_RATE_8SPS);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set rate 8 sps.\n");
    res = ads1118_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check rate %s.\n", rate == ADS1118_RATE_8SPS ? "ok" : "error");
    
    /* set 16SPS */
    res = ads1118_set_rate(&gs_handle, ADS1118_RATE_16SPS);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set rate 16 sps.\n");
    res = ads1118_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check rate %s.\n", rate == ADS1118_RATE_16SPS ? "ok" : "error");
    
    /* set 32SPS */
    res = ads1118_set_rate(&gs_handle, ADS1118_RATE_32SPS);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set rate 32 sps.\n");
    res = ads1118_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check rate %s.\n", rate == ADS1118_RATE_32SPS ? "ok" : "error");
    
    /* set 64SPS */
    res = ads1118_set_rate(&gs_handle, ADS1118_RATE_64SPS);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set rate 64 sps.\n");
    res = ads1118_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check rate %s.\n", rate == ADS1118_RATE_64SPS ? "ok" : "error");
    
    /* set 128SPS */
    res = ads1118_set_rate(&gs_handle, ADS1118_RATE_128SPS);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set rate 128 sps.\n");
    res = ads1118_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check rate %s.\n", rate == ADS1118_RATE_128SPS ? "ok" : "error");
    
    /* set 250SPS */
    res = ads1118_set_rate(&gs_handle, ADS1118_RATE_250SPS);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set rate 250 sps.\n");
    res = ads1118_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check rate %s.\n", rate == ADS1118_RATE_250SPS ? "ok" : "error");
    
    /* set 475SPS */
    res = ads1118_set_rate(&gs_handle, ADS1118_RATE_475SPS);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set rate 475 sps.\n");
    res = ads1118_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check rate %s.\n", rate == ADS1118_RATE_475SPS ? "ok" : "error");
    
    /* set 860SPS */
    res = ads1118_set_rate(&gs_handle, ADS1118_RATE_860SPS);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: set rate 860 sps.\n");
    res = ads1118_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get rate failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check rate %s.\n", rate == ADS1118_RATE_860SPS ? "ok" : "error");
    
    /* ads1118_set_dout_pull_up/ads1118_get_dout_pull_up test */
    ads1118_interface_debug_print("ads1118: ads1118_set_dout_pull_up/ads1118_get_dout_pull_up test.\n");
    
    /* disable dout pull up */
    res = ads1118_set_dout_pull_up(&gs_handle, ADS1118_BOOL_FALSE);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set dout pull up failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: disable dout pull up.\n");
    res = ads1118_get_dout_pull_up(&gs_handle, &enable);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get dout pull up failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check dout pull up %s.\n", enable == ADS1118_BOOL_FALSE ? "ok" : "error");
    
    /* enable dout pull up */
    res = ads1118_set_dout_pull_up(&gs_handle, ADS1118_BOOL_TRUE);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: set dout pull up failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: enable dout pull up.\n");
    res = ads1118_get_dout_pull_up(&gs_handle, &enable);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: get dout pull up failed.\n");
        (void)ads1118_deinit(&gs_handle);
        
        return 1;
    }
    ads1118_interface_debug_print("ads1118: check dout pull up %s.\n", enable == ADS1118_BOOL_TRUE ? "ok" : "error");
    
    /* finish register */
    ads1118_interface_debug_print("ads1118: finish register test.\n");
    (void)ads1118_deinit(&gs_handle);
    
    return 0;
}
