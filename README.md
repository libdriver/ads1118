[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ADS1118

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ads1118/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The ADS1118 is a precision, low power, 16-bit analog-to-digital converter (ADC) that provides all features necessary to measure the most common sensor signals in an ultra-small, leadless X2QFN-10 package or a VSSOP-10 package. The ADS1118 integrates a programmable gain amplifier (PGA), voltage reference, oscillator and high-accuracy temperature sensor. These features, along with a wide power supply range from 2 V to 5.5 V, make the ADS1118 ideally suited for power- and spaceconstrained, sensor-measurement applications. The ADS1118 can perform conversions at data rates up to 860 samples per second (SPS). The PGA offers input ranges from ±256 mV to ±6.144 V, allowing both large and small signals to be measured with high resolution. An input multiplexer (MUX) allows to measure two differential or four single-ended inputs. The high-accuracy temperature sensor can be used for system-level temperature monitoring or coldjunction compensation for thermocouples.

LibDriver ADS1118 is the full function driver of ADS1118 launched by LibDriver. LibDriver ADS1118 provides continuous mode ADC conversion, single mode ADC conversion, multi-channel sampling switching, temperature reading and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver ADS1118 source files.

/interface includes LibDriver ADS1118 SPI platform independent template.

/test includes LibDriver ADS1118 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver ADS1118 sample code.

/doc includes LibDriver ADS1118 offline document.

/datasheet includes ADS1118 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface SPI platform independent template and finish your platform SPI driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_ads1118_basic.h"

uint8_t res;
uint8_t i;
float s;

res = ads1118_basic_init(ADS1118_MODE_ADC, ADS1118_CHANNEL_AIN0_AIN1);
if (res != 0)
{
    ads1118_interface_debug_print("ads1118: basic init failed.\n");         

    return 1;

}

...

for (i = 0; i < 3; i++)
{
    res = ads1118_basic_read((float *)&s);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: basic read failed.\n");
        (void)ads1118_basic_deinit();

        return 1;
    }
    ads1118_interface_debug_print("ads1118: adc is %0.4fV.\n", s);
    ads1118_interface_delay_ms(1000);
    
    ...

}

...
    
(void)ads1118_basic_deinit();

return 0;
```

#### example shot

```C
#include "driver_ads1118_shot.h"

uint8_t res;
uint8_t i;
float s;

res = ads1118_shot_init(ADS1118_MODE_ADC, ADS1118_CHANNEL_AIN0_AIN1);
if (res != 0)
{
    ads1118_interface_debug_print("ads1118: shot init failed.\n");         

    return 1;

}

...
    
for (i = 0; i < 3; i++)
{
    res = ads1118_shot_read((float *)&s);
    if (res != 0)
    {
        ads1118_interface_debug_print("ads1118: shot read failed.\n");
        (void)ads1118_shot_deinit();

        return 1;
    }
    ads1118_interface_debug_print("ads1118: adc is %0.4fV.\n", s);
    ads1118_interface_delay_ms(1000);
    
    ...

}

...
    
(void)ads1118_shot_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/ads1118/index.html](https://www.libdriver.com/docs/ads1118/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.