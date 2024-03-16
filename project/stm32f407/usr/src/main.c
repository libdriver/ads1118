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
 * @file      main.c
 * @brief     main source file
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

#include "driver_ads1118_mutichannel_test.h"
#include "driver_ads1118_read_test.h"
#include "driver_ads1118_register_test.h"
#include "driver_ads1118_basic.h"
#include "driver_ads1118_shot.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];             /**< uart buffer */
volatile uint16_t g_len;        /**< uart buffer length */

/**
 * @brief     ads1118 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t ads1118(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    char short_options[] = "hipe:t:";
    struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"channel", required_argument, NULL, 1},
        {"times", required_argument, NULL, 2},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    ads1118_channel_t channel = ADS1118_CHANNEL_AIN0_GND;

    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }

    /* init 0 */
    optind = 0;

    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);

        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");

                break;
            }

            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");

                break;
            }

            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");

                break;
            }

            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);

                break;
            }

            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);

                break;
            }

            /* channel */
            case 1 :
            {
                /* set the channel */
                if (strcmp("AIN0_AIN1", optarg) == 0)
                {
                    channel = ADS1118_CHANNEL_AIN0_AIN1;
                }
                else if (strcmp("AIN0_AIN3", optarg) == 0)
                {
                    channel = ADS1118_CHANNEL_AIN0_AIN3;
                }
                else if (strcmp("AIN1_AIN3", optarg) == 0)
                {
                    channel = ADS1118_CHANNEL_AIN1_AIN3;
                }
                else if (strcmp("AIN2_AIN3", optarg) == 0)
                {
                    channel = ADS1118_CHANNEL_AIN2_AIN3;
                }
                else if (strcmp("AIN0_GND", optarg) == 0)
                {
                    channel = ADS1118_CHANNEL_AIN0_GND;
                }
                else if (strcmp("AIN1_GND", optarg) == 0)
                {
                    channel = ADS1118_CHANNEL_AIN1_GND;
                }
                else if (strcmp("AIN2_GND", optarg) == 0)
                {
                    channel = ADS1118_CHANNEL_AIN2_GND;
                }
                else if (strcmp("AIN3_GND", optarg) == 0)
                {
                    channel = ADS1118_CHANNEL_AIN3_GND;
                }
                else
                {
                    return 5;
                }

                break;
            }

            /* running times */
            case 2 :
            {
                /* set the times */
                times = atol(optarg);

                break;
            }

            /* the end */
            case -1 :
            {
                break;
            }

            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run the reg test */
        if (ads1118_register_test() != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run the read test */
        if (ads1118_read_test(times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_muti", type) == 0)
    {
        /* run the multichannel test */
        if (ads1118_multichannel_test(channel, times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float s;

        /* basic init */
        res = ads1118_basic_init(ADS1118_MODE_ADC, channel);
        if (res != 0)
        {
            ads1118_interface_debug_print("ads1118: basic init failed.\n");

            return 1;
        }
        for (i = 0; i < times; i++)
        {
            /* read the data */
            res = ads1118_basic_read((float *)&s);
            if (res != 0)
            {
                ads1118_interface_debug_print("ads1118: basic read failed.\n");
                (void)ads1118_basic_deinit();

                return 1;
            }
            ads1118_interface_debug_print("ads1118: %d/%d.\n", i + 1, times);
            ads1118_interface_debug_print("ads1118: adc is %0.4fV.\n", s);
            ads1118_interface_delay_ms(1000);
        }
        (void)ads1118_basic_deinit();

        return 0;
    }
    else if (strcmp("e_shot", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float s;

        /* shot init */
        res = ads1118_shot_init(ADS1118_MODE_ADC, channel);
        if (res != 0)
        {
            ads1118_interface_debug_print("ads1118: shot init failed.\n");

            return 1;
        }
        for (i = 0; i < times; i++)
        {
            /* read the data */
            res = ads1118_shot_read((float *)&s);
            if (res != 0)
            {
                ads1118_interface_debug_print("ads1118: shot read failed.\n");
                (void)ads1118_shot_deinit();

                return 1;
            }
            ads1118_interface_debug_print("ads1118: %d/%d.\n", i + 1, times);
            ads1118_interface_debug_print("ads1118: adc is %0.4fV.\n", s);
            ads1118_interface_delay_ms(1000);
        }
        (void)ads1118_shot_deinit();

        return 0;
    }
    else if (strcmp("e_temperature", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float s;

        /* shot init */
        res = ads1118_shot_init(ADS1118_MODE_TEMPERATURE, channel);
        if (res != 0)
        {
            ads1118_interface_debug_print("ads1118: shot init failed.\n");

            return 1;
        }
        for (i = 0; i < times; i++)
        {
            /* read the data */
            res = ads1118_shot_read_temperature((float *)&s);
            if (res != 0)
            {
                ads1118_interface_debug_print("ads1118: shot read failed.\n");
                (void)ads1118_shot_deinit();

                return 1;
            }
            ads1118_interface_debug_print("ads1118: %d/%d.\n", i + 1, times);
            ads1118_interface_debug_print("ads1118: temperature is %0.2fC.\n", s);
            ads1118_interface_delay_ms(1000);
        }
        (void)ads1118_shot_deinit();

        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        ads1118_interface_debug_print("Usage:\n");
        ads1118_interface_debug_print("  ads1118 (-i | --information)\n");
        ads1118_interface_debug_print("  ads1118 (-h | --help)\n");
        ads1118_interface_debug_print("  ads1118 (-p | --port)\n");
        ads1118_interface_debug_print("  ads1118 (-t reg | --test=reg)\n");
        ads1118_interface_debug_print("  ads1118 (-t read | --test=read) [--times=<num>]\n");
        ads1118_interface_debug_print("  ads1118 (-t muti | --test=muti) [--times=<num>]\n");
        ads1118_interface_debug_print("          [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>]\n");
        ads1118_interface_debug_print("  ads1118 (-e read | --example=read) [--times=<num>]\n");
        ads1118_interface_debug_print("          [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>]\n");
        ads1118_interface_debug_print("  ads1118 (-e shot | --example=shot) [--times=<num>]\n");
        ads1118_interface_debug_print("          [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>]\n");
        ads1118_interface_debug_print("  ads1118 (-e temperature | --example=temperature) [--times=<num>]\n");
        ads1118_interface_debug_print("\n");
        ads1118_interface_debug_print("Options:\n");
        ads1118_interface_debug_print("      --channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>\n");
        ads1118_interface_debug_print("                                         Set the ADC channel.([default: AIN0_GND])\n");
        ads1118_interface_debug_print("  -e <read | shot | temperature>, --example=<read | shot | temperature>\n");
        ads1118_interface_debug_print("                                         Run the driver example.\n");
        ads1118_interface_debug_print("  -h, --help                             Show the help.\n");
        ads1118_interface_debug_print("  -i, --information                      Show the chip information.\n");
        ads1118_interface_debug_print("  -p, --port                             Display the pin connections of the current board.\n");
        ads1118_interface_debug_print("  -t <reg | read | muti>, --test=<reg | read | muti>.\n");
        ads1118_interface_debug_print("                                         Run the driver test.\n");
        ads1118_interface_debug_print("      --times=<num>                      Set the running times.([default: 3])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        ads1118_info_t info;

        /* print ads1118 info */
        ads1118_info(&info);
        ads1118_interface_debug_print("ads1118: chip is %s.\n", info.chip_name);
        ads1118_interface_debug_print("ads1118: manufacturer is %s.\n", info.manufacturer_name);
        ads1118_interface_debug_print("ads1118: interface is %s.\n", info.interface);
        ads1118_interface_debug_print("ads1118: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ads1118_interface_debug_print("ads1118: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ads1118_interface_debug_print("ads1118: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ads1118_interface_debug_print("ads1118: max current is %0.2fmA.\n", info.max_current_ma);
        ads1118_interface_debug_print("ads1118: max temperature is %0.1fC.\n", info.temperature_max);
        ads1118_interface_debug_print("ads1118: min temperature is %0.1fC.\n", info.temperature_min);

        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        ads1118_interface_debug_print("ads1118: SPI interface SCK connected to GPIOA PIN5.\n");
        ads1118_interface_debug_print("ads1118: SPI interface MISO connected to GPIOA PIN6.\n");
        ads1118_interface_debug_print("ads1118: SPI interface MOSI connected to GPIOA PIN7.\n");
        ads1118_interface_debug_print("ads1118: SPI interface CS connected to GPIOA PIN4.\n");

        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;

    /* stm32f407 clock init and hal init */
    clock_init();

    /* delay init */
    delay_init();

    /* uart init */
    uart_init(115200);

    /* shell init && register ads1118 function */
    shell_init();
    shell_register("ads1118", ads1118);
    uart_print("ads1118: welcome to libdriver ads1118.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("ads1118: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("ads1118: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("ads1118: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("ads1118: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("ads1118: param is invalid.\n");
            }
            else
            {
                uart_print("ads1118: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
