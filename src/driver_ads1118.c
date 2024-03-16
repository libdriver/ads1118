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
 * @file      driver_ads1118.c
 * @brief     driver ads1118 source file
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

#include "driver_ads1118.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Texas Instruments ADS1118"        /**< chip name */
#define MANUFACTURER_NAME         "Texas Instruments"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.0f                               /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                               /**< chip max supply voltage */
#define MAX_CURRENT               0.3f                               /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                             /**< chip min operating temperature */
#define TEMPERATURE_MAX           125.0f                             /**< chip max operating temperature */
#define DRIVER_VERSION            1000                               /**< driver version */

/**
 * @brief command definition
 */
#define COMMAND_VALID        (1 << 1)        /**< valid command */

/**
 * @brief      read bytes
 * @param[in]  *handle points to an ads1118 handle structure
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_ads1118_spi_read(ads1118_handle_t *handle, uint16_t *data)
{
    uint8_t tx_buf[4];
    uint8_t rx_buf[4];
    
    tx_buf[0] = 0xFF;                                                  /* 0xFF */
    tx_buf[1] = 0xFF;                                                  /* 0xFF */
    tx_buf[2] = 0xFF;                                                  /* 0xFF */
    tx_buf[3] = 0xFF;                                                  /* 0xFF */
    if (handle->spi_transmit(tx_buf, rx_buf, 4) != 0)                  /* transmit */
    {
        return 1;                                                      /* return error */
    }
    *data = (uint16_t)((uint16_t)(rx_buf[2]) << 8) | rx_buf[3];        /* get data */
    
    return 0;                                                          /* success return 0 */
}

/**
 * @brief      read data bytes
 * @param[in]  *handle points to an ads1118 handle structure
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_ads1118_spi_read_data(ads1118_handle_t *handle, int16_t *data)
{
    uint8_t tx_buf[2];
    uint8_t rx_buf[2];
    
    tx_buf[0] = 0xFF;                                                 /* 0xFF */
    tx_buf[1] = 0xFF;                                                 /* 0xFF */
    if (handle->spi_transmit(tx_buf, rx_buf, 2) != 0)                 /* transmit */
    {
        return 1;                                                     /* return error */
    }
    *data = (int16_t)((uint16_t)(rx_buf[0]) << 8) | rx_buf[1];        /* get data */
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief     write bytes
 * @param[in] *handle points to an ads1118 handle structure
 * @param[in] data is the sent data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_ads1118_spi_write(ads1118_handle_t *handle, uint16_t data)
{
    uint8_t tx_buf[2];
    uint8_t rx_buf[2];
    
    tx_buf[0] = (data >> 8) & 0xFF;                          /* set msb */
    tx_buf[1] = (data >> 0) & 0xFF;                          /* set lsb */
    if (handle->spi_transmit(tx_buf, rx_buf, 2) != 0)        /* transmit */
    {
        return 1;                                            /* return error */
    }
    
    return 0;                                                /* success return 0 */
}

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
uint8_t ads1118_init(ads1118_handle_t *handle)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->debug_print == NULL)                                 /* check debug_print */
    {
        return 3;                                                    /* return error */
    }
    if (handle->spi_init == NULL)                                    /* check spi_init */
    {
        handle->debug_print("ads1118: spi_init is null.\n");         /* spi_init is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->spi_deinit == NULL)                                  /* check spi_deinit */
    {
        handle->debug_print("ads1118: spi_deinit is null.\n");       /* spi_deinit is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->spi_transmit == NULL)                                /* check spi_transmit */
    {
        handle->debug_print("ads1118: spi_transmit is null.\n");     /* spi_transmit is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->delay_ms == NULL)                                    /* check delay_ms */
    {
        handle->debug_print("ads1118: delay_ms is null.\n");         /* delay_ms is null */
        
        return 3;                                                    /* return error */
    }
    
    if (handle->spi_init() != 0)                                     /* spi init */
    {
        handle->debug_print("ads1118: spi init failed.\n");          /* spi init failed */
        
        return 1;                                                    /* return error */
    }
    handle->inited = 1;                                              /* flag inited */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ads1118_deinit(ads1118_handle_t *handle)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);               /* read config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");         /* read config failed */
        
        return 4;                                                      /* return error */
    }
    conf &= ~(0x01 << 8);                                              /* clear bit */
    conf |= 1 << 8;                                                    /* set stop continues read */
    res = a_ads1118_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: write config failed.\n");        /* write config failed */
        
        return 4;                                                      /* return error */
    }
    res = handle->spi_deinit();                                        /* close spi */
    if (res != 0)                                                      /* check the result */
    {
        handle->debug_print("ads1118: spi deinit failed.\n");          /* spi deinit failed */
        
        return 1;                                                      /* return error */
    }
    handle->inited = 0;                                                /* flag close */
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t ads1118_set_channel(ads1118_handle_t *handle, ads1118_channel_t channel)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);               /* read config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");         /* read config failed */
        
        return 1;                                                      /* return error */
    }
    conf &= ~(0x07 << 12);                                             /* clear channel */
    conf |= (channel & 0x07) << 12;                                    /* set channel */
    conf &= ~(3 << 1);                                                 /* clear nop */
    conf |= COMMAND_VALID;                                             /* set command valid */
    res = a_ads1118_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: write config failed.\n");        /* write config failed */
        
        return 1;                                                      /* return error */
    }
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t ads1118_get_channel(ads1118_handle_t *handle, ads1118_channel_t *channel)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);              /* read config */
    if (res != 0)                                                     /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");        /* read config failed */
        
        return 1;                                                     /* return error */
    }
    *channel = (ads1118_channel_t)((conf >> 12) & 0x07);              /* get channel */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ads1118_set_range(ads1118_handle_t *handle, ads1118_range_t range)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);               /* read config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");         /* read config failed */
        
        return 1;                                                      /* return error */
    }
    conf &= ~(0x07 << 9);                                              /* clear range */
    conf |= (range & 0x07) << 9;                                       /* set range */
    conf &= ~(3 << 1);                                                 /* clear nop */
    conf |= COMMAND_VALID;                                             /* set command valid */
    res = a_ads1118_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: write config failed.\n");        /* write config failed */
        
        return 1;                                                      /* return error */
    }
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t ads1118_get_range(ads1118_handle_t *handle, ads1118_range_t *range)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);              /* read config */
    if (res != 0)                                                     /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");        /* read config failed */
        
        return 1;                                                     /* return error */
    }
    *range = (ads1118_range_t)((conf >> 9) & 0x07);                   /* get range */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ads1118_set_rate(ads1118_handle_t *handle, ads1118_rate_t rate)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);               /* read config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");         /* read config failed */
        
        return 1;                                                      /* return error */
    }
    conf &= ~(0x07 << 5);                                              /* clear rate */
    conf |= (rate & 0x07) << 5;                                        /* set rate */
    conf &= ~(3 << 1);                                                 /* clear nop */
    conf |= COMMAND_VALID;                                             /* set command valid */
    res = a_ads1118_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: write config failed.\n");        /* write config failed */
        
        return 1;                                                      /* return error */
    }
    
    return 0;                                                          /* success return */
}

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
uint8_t ads1118_get_rate(ads1118_handle_t *handle, ads1118_rate_t *rate)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);              /* read config */
    if (res != 0)                                                     /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");        /* read config failed */
        
        return 1;                                                     /* return error */
    }
    *rate = (ads1118_rate_t)((conf >> 5) & 0x07);                     /* get rate */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ads1118_set_mode(ads1118_handle_t *handle, ads1118_mode_t mode)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);               /* read config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");         /* read config failed */
        
        return 1;                                                      /* return error */
    }
    conf &= ~(1 << 4);                                                 /* clear settings */
    conf |= mode << 4;                                                 /* set mode */
    conf &= ~(3 << 1);                                                 /* clear nop */
    conf |= COMMAND_VALID;                                             /* set command valid */
    res = a_ads1118_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: write config failed.\n");        /* write config failed */
        
        return 1;                                                      /* return error */
    }
    
    return 0;                                                          /* success return */
}

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
uint8_t ads1118_get_mode(ads1118_handle_t *handle, ads1118_mode_t *mode)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);              /* read config */
    if (res != 0)                                                     /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");        /* read config failed */
        
        return 1;                                                     /* return error */
    }
    *mode = (ads1118_mode_t)((conf >> 4) & 0x01);                     /* get mode */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ads1118_set_dout_pull_up(ads1118_handle_t *handle, ads1118_bool_t enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);               /* read config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");         /* read config failed */
        
        return 1;                                                      /* return error */
    }
    conf &= ~(1 << 3);                                                 /* clear settings */
    conf |= enable << 3;                                               /* set enable */
    conf &= ~(3 << 1);                                                 /* clear nop */
    conf |= COMMAND_VALID;                                             /* set command valid */
    res = a_ads1118_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: write config failed.\n");        /* write config failed */
        
        return 1;                                                      /* return error */
    }
    
    return 0;                                                          /* success return */
}

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
uint8_t ads1118_get_dout_pull_up(ads1118_handle_t *handle, ads1118_bool_t *enable)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);               /* read config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");         /* read config failed */
        
        return 1;                                                      /* return error */
    }
    *enable = (ads1118_bool_t)((conf >> 3) & 0x01);                    /* get bool */
    
    return 0;                                                          /* success return */
}

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
uint8_t ads1118_single_read(ads1118_handle_t *handle, int16_t *raw, float *v)
{
    uint8_t res;
    uint8_t range;
    uint16_t conf;
    uint32_t timeout = 500;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);                  /* read config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");            /* read config failed */
        
        return 1;                                                         /* return error */
    }
    range = (ads1118_range_t)((conf >> 9) & 0x07);                        /* get range conf */
    conf &= ~(1 << 8);                                                    /* clear bit */
    conf |= 1 << 8;                                                       /* set single read */
    conf |= 1 << 15;                                                      /* start single read */
    res = a_ads1118_spi_write(handle, conf);                              /* write config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("ads1118: write config failed.\n");           /* write config failed */
        
        return 1;                                                         /* return error */
    }
    while (timeout != 0)                                                  /* check timeout */
    {
        handle->delay_ms(8);                                              /* wait 8 ms */
        res = a_ads1118_spi_read(handle, (uint16_t *)&conf);              /* read config */
        if (res != 0)                                                     /* check error */
        {
            handle->debug_print("ads1118: read config failed.\n");        /* read config failed */
            
            return 1;                                                     /* return error */
        }
        if ((conf & (1 << 15)) == (1 << 15))                              /* check finished */
        {
            break;                                                        /* break */
        }
        timeout--;                                                        /* timeout-- */
    }
    if (timeout == 0)                                                     /* check timeout */
    {
        handle->debug_print("ads1118: read timeout.\n");                  /* timeout */
        
        return 1;                                                         /* return error */
    }
    res = a_ads1118_spi_read_data(handle, raw);                           /* read data */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("ads1118: continues read failed.\n");         /* continues read failed */
        
        return 1;                                                         /* return error */
    }
    if (range == ADS1118_RANGE_6P144V)                                    /* if 6.144V */
    {
        *v = (float)(*raw) * 6.144f / 32768.0f;                           /* get convert adc */
    }
    else if (range == ADS1118_RANGE_4P096V)                               /* if 4.096V */
    {
        *v = (float)(*raw) * 4.096f / 32768.0f;                           /* get convert adc */
    }
    else if (range == ADS1118_RANGE_2P048V)                               /* if 2.048V */
    {
        *v = (float)(*raw) * 2.048f / 32768.0f;                           /* get convert adc */
    }
    else if (range == ADS1118_RANGE_1P024V)                               /* if 1.024V */
    {
        *v = (float)(*raw) * 1.024f / 32768.0f;                           /* get convert adc */
    }
    else if (range == ADS1118_RANGE_0P512V)                               /* if 0.512V */
    {
        *v = (float)(*raw) * 0.512f / 32768.0f;                           /* get convert adc */
    }
    else if (range == ADS1118_RANGE_0P256V)                               /* if 0.256V */
    {
        *v = (float)(*raw) * 0.256f / 32768.0f;                           /* get convert adc */
    }
    else
    {
        handle->debug_print("ads1118: range is invalid.\n");              /* range is invalid */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t ads1118_continuous_read(ads1118_handle_t *handle, int16_t *raw, float *v)
{
    uint8_t res;
    uint8_t range;
    uint16_t conf;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);                  /* read config */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");            /* read config failed */
        
        return 1;                                                         /* return error */
    }
    range = (ads1118_range_t)((conf >> 9) & 0x07);                        /* get range conf */
    res = a_ads1118_spi_read_data(handle, raw);                           /* read data */
    if (res != 0)                                                         /* check error */
    {
        handle->debug_print("ads1118: continuous read failed.\n");        /* continuous read failed */
        
        return 1;                                                         /* return error */
    }
    if (range == ADS1118_RANGE_6P144V)                                    /* if 6.144V */
    {
        *v = (float)(*raw) * 6.144f / 32768.0f;                           /* get convert adc */
    }
    else if (range == ADS1118_RANGE_4P096V)                               /* if 4.096V */
    {
        *v = (float)(*raw) * 4.096f / 32768.0f;                           /* get convert adc */
    }
    else if (range == ADS1118_RANGE_2P048V)                               /* if 2.048V */
    {
        *v = (float)(*raw) * 2.048f / 32768.0f;                           /* get convert adc */
    }
    else if (range == ADS1118_RANGE_1P024V)                               /* if 1.024V */
    {
        *v = (float)(*raw) * 1.024f / 32768.0f;                           /* get convert adc */
    }
    else if (range == ADS1118_RANGE_0P512V)                               /* if 0.512V */
    {
        *v = (float)(*raw) * 0.512f / 32768.0f;                           /* get convert adc */
    }
    else if (range == ADS1118_RANGE_0P256V)                               /* if 0.256V */
    {
        *v = (float)(*raw) * 0.256f / 32768.0f;                           /* get convert adc */
    }
    else
    {
        handle->debug_print("ads1118: range is invalid.\n");              /* range is invalid */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t ads1118_start_continuous_read(ads1118_handle_t *handle)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);               /* read config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");         /* read config failed */
        
        return 1;                                                      /* return error */
    }
    conf &= ~(0x01 << 8);                                              /* set start continuous read */
    res = a_ads1118_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: write config failed.\n");        /* write config failed */
        
        return 1;                                                      /* return error */
    }
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t ads1118_stop_continuous_read(ads1118_handle_t *handle)
{
    uint8_t res;
    uint16_t conf;
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_ads1118_spi_read(handle, (uint16_t *)&conf);               /* read config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: read config failed.\n");         /* read config failed */
        
        return 1;                                                      /* return error */
    }
    conf &= ~(0x01 << 8);                                              /* clear bit */
    conf |= 1 << 8;                                                    /* set stop continues read */
    res = a_ads1118_spi_write(handle, conf);                           /* write config */
    if (res != 0)                                                      /* check error */
    {
        handle->debug_print("ads1118: write config failed.\n");        /* write config failed */
        
        return 1;                                                      /* return error */
    }
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t ads1118_temperature_convert(ads1118_handle_t *handle, int16_t raw, float *deg)
{
    if (handle == NULL)                           /* check handle */
    {
        return 2;                                 /* return error */
    }
    if (handle->inited != 1)                      /* check handle initialization */
    {
        return 3;                                 /* return error */
    }
    
    *deg = (float)(raw) * 0.03125f / 4.0f;        /* convert to deg */
    
    return 0;                                     /* success return 0 */
}

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
uint8_t ads1118_transmit(ads1118_handle_t *handle, uint8_t *tx, uint8_t *rx, uint16_t len)
{
    if (handle == NULL)                                /* check handle */
    {
        return 2;                                      /* return error */
    }
    if (handle->inited != 1)                           /* check handle initialization */
    {
        return 3;                                      /* return error */
    }
    
    if (handle->spi_transmit(tx, rx, len) != 0)        /* spi transmit */
    {
        return 1;                                      /* return error */
    }
    
    return 0;                                          /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an ads1118 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ads1118_info(ads1118_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(ads1118_info_t));                        /* initialize ads1118 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "SPI", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
