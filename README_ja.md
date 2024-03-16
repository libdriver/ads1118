[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ADS1118

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ads1118/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ADS1118 は、高精度、低消費電力、16 ビットのアナログ - デジタル コンバータ (ADC) で、最も一般的なセンサー信号の測定に必要なすべての機能を超小型のリードレス X2QFN-10 パッケージまたは VSSOP-10 パッケージで提供します。 。 ADS1118 には、プログラマブル ゲイン アンプ (PGA)、電圧リファレンス、発振器、高精度温度センサーが統合されています。 これらの機能と 2 V ～ 5.5 V の広い電源範囲により、ADS1118 は電力とスペースに制約のあるセンサー測定アプリケーションに最適です。 ADS1118 は、最大 860 サンプル/秒 (SPS) のデータ レートで変換を実行できます。 PGA は±256 mV ～ ±6.144 V の入力範囲を提供し、大信号と小信号の両方を高分解能で測定できます。 入力マルチプレクサ (MUX) により、2 つの差動入力または 4 つのシングルエンド入力を測定できます。 高精度温度センサーは、システムレベルの温度監視や熱電対の冷接点補償に使用できます。

LibDriver ADS1118 は、LibDriver によって起動される ADS1118 の全機能ドライバーです。 LibDriver ADS1118 は、連続モード ADC 変換、シングル モード ADC 変換、マルチチャネル サンプリング スイッチング、温度読み取りおよびその他の機能を提供します。 LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver ADS1118のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver ADS1118用のプラットフォームに依存しないSPIバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver ADS1118ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver ADS1118プログラミング例が含まれています。

/ docディレクトリには、LibDriver ADS1118オフラインドキュメントが含まれています。

/ datasheetディレクトリには、ADS1118データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないSPIバステンプレートを参照して、指定したプラットフォームのSPIバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

```c
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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/ads1118/index.html](https://www.libdriver.com/docs/ads1118/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。