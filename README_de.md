[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ADS1118

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ads1118/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der ADS1118 ist ein präziser 16-Bit-Analog-Digital-Wandler (ADC) mit geringem Stromverbrauch, der alle erforderlichen Funktionen zum Messen der gängigsten Sensorsignale in einem ultrakleinen, unbedrahteten X2QFN-10-Gehäuse oder einem VSSOP-10-Gehäuse bietet . Der ADS1118 integriert einen Verstärker mit programmierbarer Verstärkung (PGA), eine Spannungsreferenz, einen Oszillator und einen hochpräzisen Temperatursensor. Aufgrund dieser Merkmale sowie eines großen Spannungsversorgungsbereichs von 2 V bis 5,5 V eignet sich der ADS1118 ideal für Sensormessanwendungen mit eingeschränkter Stromversorgung und Platzbedarf. Der ADS1118 kann Konvertierungen mit Datenraten von bis zu 860 Samples pro Sekunde (SPS) durchführen. Der PGA bietet Eingangsbereiche von ±256 mV bis ±6,144 V, sodass sowohl große als auch kleine Signale mit hoher Auflösung gemessen werden können. Ein Eingangsmultiplexer (MUX) ermöglicht die Messung von zwei differenziellen oder vier Single-Ended-Eingängen. Der hochpräzise Temperatursensor kann zur Temperaturüberwachung auf Systemebene oder zur Kaltstellenkompensation für Thermoelemente verwendet werden.

LibDriver ADS1118 ist der von LibDriver gestartete Vollfunktionstreiber von ADS1118. LibDriver ADS1118 bietet ADC-Konvertierung im kontinuierlichen Modus, ADC-Konvertierung im Einzelmodus, Mehrkanal-Abtastumschaltung, Temperaturmessung und andere Funktionen. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver ADS1118-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver ADS1118 SPI.

/test enthält den Testcode des LibDriver ADS1118-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver ADS1118-Beispielcode.

/doc enthält das LibDriver ADS1118-Offlinedokument.

/Datenblatt enthält ADS1118-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige SPI-Schnittstellenvorlage und stellen Sie Ihren Plattform-SPI-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/ads1118/index.html](https://www.libdriver.com/docs/ads1118/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.