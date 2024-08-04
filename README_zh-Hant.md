[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ADS1118

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ads1118/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ADS1118是一款精密的低功耗16比特模數轉換器（ADC），它採用超小型無引線X2QFN-10封裝或VSSOP-10封裝。 ADS1118集成了可程式設計增益放大器（PGA）、電壓基準、振盪器和高精度溫度感測器。 這些功能以及2V至5.5V的寬電源電壓範圍，這使得ADS1118非常適合功率受限和空間受限的感測器量測應用。 ADS1118資料轉換速率最高可達每秒860次採樣（SPS）。 PGA的輸入範圍為±256mV至±6.144V，能够以高解析度量測大訊號和小訊號。 該器件通過輸入多工器（MUX）量測雙路差分輸入或四路單端輸入。 高精度溫度感測器用於系統級溫度監控或對熱電偶進行冷結點補償。

LibDriver ADS1118是LibDriver推出的ADS1118的全功能驅動，該驅動提供連續模式模數轉換、單次模式模數轉換，多通道採樣切換，內部溫度讀取等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver ADS1118的源文件。

/interface目錄包含了LibDriver ADS1118與平台無關的SPI總線模板。

/test目錄包含了LibDriver ADS1118驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver ADS1118編程範例。

/doc目錄包含了LibDriver ADS1118離線文檔。

/datasheet目錄包含了ADS1118數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的SPI總線模板，完成指定平台的SPI總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/ads1118/index.html](https://www.libdriver.com/docs/ads1118/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。