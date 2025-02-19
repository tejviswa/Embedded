## Hardware connection STM32f401Rbt6 -> TFTLCD(1.8)
| PORT TFT | PORT STM32F401RBT6 | Description |
| :--- | :--- |  :--- |
| RST | GPIOA-1 | Chip Reset Signal |
| CS | GPIOA-4 | SPI Chip Select |
| D/C or A0 | GPIOA-0 | SPI data / command; 1=Data, 0=Command |
| SDA | GPIOA-7 | SPI Serial data in / MOSI |
| SCL | GPIOA-5 | SPI Serial clock signal |
| VCC | +5V | Supply Voltage +5V |
| GND | GND | Ground |