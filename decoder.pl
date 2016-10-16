use Device::BCM2835;
use strict;

#From http://elinux.org/RPi_GPIO_Code_Samples
Device::BCM2835::init()
    die "Could not init library";
# Set pins 14 and 15 to input and output as RX and TX
Device::BCM2835::gpio_fsel(&Device::BCM2835::RPI_GPIO_P1_14, &Device::BCM2835::BCM2835_GPIO_FSEL_INP);
Device::BCM2835::gpio_fsel(&Device::BCM2835::RPI_GPIO_P1_15, &Device::BCM2835::BCM2835_GPIO_FSEL_OUTP);

#GPIO 9,10,11 for SPI
Device::BCM2835::gpio_fsel(&Device::BCM2835::RPI_GPIO_P1_9, &Device::BCM2835::BCM2835_GPIO_FSEL_ALT0);
Device::BCM2835::gpio_fsel(&Device::BCM2835::RPI_GPIO_P1_10, &Device::BCM2835::BCM2835_GPIO_FSEL_ALT0);
Device::BCM2835::gpio_fsel(&Device::BCM2835::RPI_GPIO_P1_11, &Device::BCM2835::BCM2835_GPIO_FSEL_ALT0);

#GPIO 17
Device::BCM2835::gpio_fsel(&Device::BCM2835::RPI_GPIO_P1_17, &Device::BCM2835::BCM2835_GPIO_FSEL_INP);
