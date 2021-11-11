LIBADI_DAUGHTERBOARD = libadi_daughterboard.a
CC = aarch64-linux-gnu-gcc
ADI_ADRV9025_DAUGHTERBOARD_SRC = ./adrv9025/src
ADI_AD9528_DAUGHTERBOARD_SRC = ./ad9528/src
ADI_FPGA9025_DAUGHTERBOARD_SRC = ./fpga9025
ADI_FPGA9010_DAUGHTERBOARD_SRC = ./fpga9010

ARFLAGS = -rv
CFLAGS = -Wall -Werror -I ./adrv9025/include -I ../motherboards -I ../daughterboards -I ../../devices/adrv9025/public/include/ -I ../../devices/fpga9010/public/include/ -I ../../devices/fpga9025/public/include/ -I ../../devices/ad9528/public/include/ -I ../../platforms/ -I ../../platforms/platform_utils -I ../../common/  -I ../../common/adi_error -I ../../common/adi_logging -I../../common/adi_hal 
EXT = c

SRC = $(wildcard *.$(EXT)) \
        $(wildcard $(ADI_ADRV9025_DAUGHTERBOARD_SRC)/*.$(EXT) \
        $(ADI_AD9528_DAUGHTERBOARD_SRC)/*.$(EXT) \
        $(ADI_FPGA9025_DAUGHTERBOARD_SRC)/*.$(EXT) \
        $(ADI_FPGA9010_DAUGHTERBOARD_SRC)/*.$(EXT))

OBJS = $(SRC:.$(EXT)=.o)

all: $(SRC) $(LIBADI_DAUGHTERBOARD)

.$(EXT).o:
	$(CC) $(CFLAGS) -DADRV9025 -o $@ -c $<

$(LIBADI_DAUGHTERBOARD): $(OBJS)
	ar $(ARFLAGS) $(LIBADI_DAUGHTERBOARD) $(OBJS)

clean:
	rm -rf *.o
	rm -rf *.a
