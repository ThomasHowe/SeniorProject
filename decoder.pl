use Device::BCM2835;
use List::Util qw(sum);
use DateTime;
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

#If a full 1 second beep is sounded, it means get the average speed after
while(Device::BCM2835::gpio_read(&Device::BCM2835::RPIO_GPIO_P1_17, 0);
$sttime = DateTime->now();
while(Device::BCM2835::gpio_read(&Device::BCM2835::RPIO_GPIO_P1_17, 1);
$endtime = DateTime->now();
$elapsed = $endtime - $sttime;
$elapsed->in_units('miliseconds');

if($elapsed > 1000) {
    #Average speed of five dots
    @speed = (0, 0, 0, 0, 0);
    for($i = 1; $i < 5; $i++) {
        while(Device::BCM2835::gpio_read(&Device::BCM2835::RPIO_GPIO_P1_17, 0);
        $sttime = DateTime->now();
        while(Device::BCM2835::gpio_read(&Device::BCM2835::RPIO_GPIO_P1_17, 1);
        $endtime = DateTime->now();
        $elapsed = $endtime - $sttime;
        $elapsed->in_units('miliseconds');
        @speed($i) = $elapsed;
    }
}

my arg1 = mean(@speed);

#Call Python script
my $ret = `/usr/bin/decode.py arg1`;

sub mean {
    return sum(@_)/@_;
}
