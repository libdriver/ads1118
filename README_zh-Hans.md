[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ADS1118

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ads1118/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ADS1118是一款精密的低功耗16 位模数转换器 (ADC)，它采用超小型无引线 X2QFN-10封装或VSSOP-10封装。ADS1118集成了可编程增益放大器 (PGA)、电压基准、振荡器和高精度温度传感器。这些功能以及 2V至 5.5V 的宽电源电压范围，这使得 ADS1118 非常适合功率受限和空间受限的传感器测量应用。ADS1118数据转换速率最高可达每秒860次采样 (SPS)。PGA的输入范围为±256mV至±6.144V，能够以高分辨率测量大信号和小信号。该器件通过输入多路复用器 (MUX) 测量双路差分输入或四路单端输入。 高精度温度传感器用于系统级温度监控或对热电偶进行冷结点补偿。

LibDriver ADS1118是LibDriver推出的ADS1118的全功能驱动，该驱动提供连续模式模数转换、单次模式模数转换，多通道采样切换，内部温度读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver ADS1118的源文件。

/interface目录包含了LibDriver ADS1118与平台无关的SPI总线模板。

/test目录包含了LibDriver ADS1118驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver ADS1118编程范例。

/doc目录包含了LibDriver ADS1118离线文档。

/datasheet目录包含了ADS1118数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的SPI总线模板，完成指定平台的SPI总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/ads1118/index.html](https://www.libdriver.com/docs/ads1118/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。