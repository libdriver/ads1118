### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

SPI Pin: SCLK/MOSI/MISO/CS GPIO11/GPIO10/GPIO9/GPIO8.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(ads1118 REQUIRED)
```

### 3. ADS1118

#### 3.1 Command Instruction

1. Show ads1118 chip and driver information.

    ```shell
    ads1118 (-i | --information)  
    ```

2. Show ads1118 help.

    ```shell
    ads1118 (-h | --help)        
    ```

3. Show ads1118 pin connections of the current board.

    ```shell
    ads1118 (-p | --port)        
    ```

4. Run ads1118 register test.

    ```shell
    ads1118 (-t reg | --test=reg)      
    ```

5. Run ads1118 read test, num means test times.

    ```shell
    ads1118 (-t read | --test=read) [--times=<num>]
    ```

6. Run ads1118 mutichannel test, num means test times.

    ```shell
    ads1118 (-t muti | --test=muti) [--times=<num>] [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>]        
    ```

8. Run ads1118 read function, num means read times.

    ```shell
    ads1118 (-e read | --example=read) [--times=<num>] [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>]      
    ```

8. Run ads1118 shot function, num means read times.

    ```shell
    ads1118 (-e shot | --example=shot) [--times=<num>] [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>]      
    ```
9. Run ads1118 temperature function, num means read times.

    ```shell
    ads1118 (-e temperature | --example=temperature) [--times=<num>]  

#### 3.2 Command Example

```shell
./ads1118 -i

ads1118: chip is Texas Instruments ADS1118.
ads1118: manufacturer is Texas Instruments.
ads1118: interface is SPI.
ads1118: driver version is 1.0.
ads1118: min supply voltage is 2.0V.
ads1118: max supply voltage is 5.5V.
ads1118: max current is 0.30mA.
ads1118: max temperature is 125.0C.
ads1118: min temperature is -40.0C.
```

```shell
./ads1118 -p

ads1118: SPI interface SCK connected to GPIO11(BCM).
ads1118: SPI interface MISO connected to GPIO9(BCM).
ads1118: SPI interface MOSI connected to GPIO10(BCM).
ads1118: SPI interface CS connected to GPIO8(BCM).
```

```shell
./ads1118 -t reg

ads1118: chip is Texas Instruments ADS1118.
ads1118: manufacturer is Texas Instruments.
ads1118: interface is SPI.
ads1118: driver version is 1.0.
ads1118: min supply voltage is 2.0V.
ads1118: max supply voltage is 5.5V.
ads1118: max current is 0.30mA.
ads1118: max temperature is 125.0C.
ads1118: min temperature is -40.0C.
ads1118: start register test.
ads1118: ads1118_set_channel/ads1118_get_channel test.
ads1118: set channel ain0_ground.
ads1118: check channel ok.
ads1118: set channel ain1_ground.
ads1118: check channel ok.
ads1118: set channel ain2_ground.
ads1118: check channel ok.
ads1118: set channel ain3_ground.
ads1118: check channel ok.
ads1118: set channel ain0_ain1.
ads1118: check channel ok.
ads1118: set channel ain0_ain3.
ads1118: check channel ok.
ads1118: set channel ain1_ain3.
ads1118: check channel ok.
ads1118: set channel ain2_ain3.
ads1118: check channel ok.
ads1118: ads1118_set_range/ads1118_get_range test.
ads1118: set range 6.144V.
ads1118: check range ok.
ads1118: set range 4.096V.
ads1118: check range ok.
ads1118: set range 2.048V.
ads1118: check range ok.
ads1118: set range 1.024V.
ads1118: check range ok.
ads1118: set range 0.512V.
ads1118: check range ok.
ads1118: set range 0.256V.
ads1118: check range ok.
ads1118: ads1118_set_mode/ads1118_get_mode test.
ads1118: set adc mode.
ads1118: check mode ok.
ads1118: set temperature mode.
ads1118: check mode ok.
ads1118: ads1118_set_rate/ads1118_get_rate test.
ads1118: set rate 8 sps.
ads1118: check rate ok.
ads1118: set rate 16 sps.
ads1118: check rate ok.
ads1118: set rate 32 sps.
ads1118: check rate ok.
ads1118: set rate 64 sps.
ads1118: check rate ok.
ads1118: set rate 128 sps.
ads1118: check rate ok.
ads1118: set rate 250 sps.
ads1118: check rate ok.
ads1118: set rate 475 sps.
ads1118: check rate ok.
ads1118: set rate 860 sps.
ads1118: check rate ok.
ads1118: ads1118_set_dout_pull_up/ads1118_get_dout_pull_up test.
ads1118: disable dout pull up.
ads1118: check dout pull up ok.
ads1118: enable dout pull up.
ads1118: check dout pull up ok.
ads1118: finish register test.
```

```shell
./ads1118 -t read --times=3

ads1118: chip is Texas Instruments ADS1118.
ads1118: manufacturer is Texas Instruments.
ads1118: interface is SPI.
ads1118: driver version is 1.0.
ads1118: min supply voltage is 2.0V.
ads1118: max supply voltage is 5.5V.
ads1118: max current is 0.30mA.
ads1118: max temperature is 125.0C.
ads1118: min temperature is -40.0C.
ads1118: start read test.
ads1118: AIN0 to GND.
ads1118: continuous read test.
ads1118: 1 continues mode 3.299V.
ads1118: 2 continues mode 3.299V.
ads1118: 3 continues mode 3.299V.
ads1118: single read test.
ads1118: 1 single mode 3.299V.
ads1118: 2 single mode 3.299V.
ads1118: 3 single mode 3.299V.
ads1118: temperature read test.
ads1118: 1 temperature is 30.938C.
ads1118: 2 temperature is 30.906C.
ads1118: 3 temperature is 30.906C.
ads1118: finish read test.
```

```shell
./ads1118 -t muti --times=3 --channel=AIN0_GND

ads1118: chip is Texas Instruments ADS1118.
ads1118: manufacturer is Texas Instruments.
ads1118: interface is SPI.
ads1118: driver version is 1.0.
ads1118: min supply voltage is 2.0V.
ads1118: max supply voltage is 5.5V.
ads1118: max current is 0.30mA.
ads1118: max temperature is 125.0C.
ads1118: min temperature is -40.0C.
ads1118: start multichannel test.
ads1118: 1/3 voltage is 3.30V.
ads1118: 2/3 voltage is 3.30V.
ads1118: 3/3 voltage is 3.30V.
ads1118: finish multichannel test.
```

```shell
./ads1118 -e read --times=3 --channel=AIN0_GND

ads1118: 1/3.
ads1118: adc is 3.2987V.
ads1118: 2/3.
ads1118: adc is 3.2987V.
ads1118: 3/3.
ads1118: adc is 3.2991V.
```

```shell
./ads1118 -e shot --times=3 --channel=AIN0_GND

ads1118: 1/3.
ads1118: adc is 3.2987V.
ads1118: 2/3.
ads1118: adc is 3.2991V.
ads1118: 3/3.
ads1118: adc is 3.2989V.
```
```shell
./ads1118 -e temperature --times=3

ads1118: 1/3.
ads1118: temperature is 30.62C.
ads1118: 2/3.
ads1118: temperature is 30.62C.
ads1118: 3/3.
ads1118: temperature is 30.62C.
```
```shell
./ads1118 -h

Usage:
  ads1118 (-i | --information)
  ads1118 (-h | --help)
  ads1118 (-p | --port)
  ads1118 (-t reg | --test=reg)
  ads1118 (-t read | --test=read) [--times=<num>]
  ads1118 (-t muti | --test=muti) [--times=<num>]
          [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>]
  ads1118 (-e read | --example=read) [--times=<num>]
          [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>]
  ads1118 (-e shot | --example=shot) [--times=<num>]
          [--channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>]
  ads1118 (-e temperature | --example=temperature) [--times=<num>]

Options:
      --channel=<AIN0_AIN1 | AIN0_AIN3 | AIN1_AIN3 | AIN2_AIN3 | AIN0_GND | AIN1_GND | AIN2_GND | AIN3_GND>
                                         Set the ADC channel.([default: AIN0_GND])
  -e <read | shot | temperature>, --example=<read | shot | temperature>
                                         Run the driver example.
  -h, --help                             Show the help.
  -i, --information                      Show the chip information.
  -p, --port                             Display the pin connections of the current board.
  -t <reg | read | muti>, --test=<reg | read | muti>.
                                         Run the driver test.
      --times=<num>                      Set the running times.([default: 3])
```
