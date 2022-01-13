LIB_ADI_FPGA9010_DEVICE = libadi_fpga9010.a
CC = aarch64-linux-gnu-gcc
ADI_FPGA9010_SRC = ./public/src
ADI_FPGA9010_PRIVATE_SRC = ./private/src
ARFLAGS = -rv
CFLAGS = -Werror -Wall -I./public/include -I../../platforms/ -I../../common/  -I../../common/adi_error -I../../common/adi_logging -I../../common/adi_hal
ADI_PLATFORM_SRC = ../../platforms
ADI_COMMON_SRC = ../../common
EXT = c

SRC = $(wildcard $(ADI_FPGA9010_PRIVATE_SRC)/*.$(EXT)) \
	$(wildcard $(ADI_FPGA9010_SRC)/*.$(EXT))

OBJS = $(SRC:.$(EXT)=.o)

all: adi_platform_lib \
	adi_common_lib \
	$(LIB_ADI_FPGA9010_DEVICE)

.$(EXT).o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIB_ADI_FPGA9010_DEVICE): $(OBJS)
	ar $(ARFLAGS) $(LIB_ADI_FPGA9010_DEVICE) $(OBJS)

adi_platform_lib:
	$(MAKE) -C $(ADI_PLATFORM_SRC)

adi_common_lib:
	$(MAKE) -C $(ADI_COMMON_SRC)

clean:
	rm -rf $(ADI_FPGA9010_SRC)/*.o
	rm -rf $(ADI_FPGA9010_PRIVATE_SRC)/*.o
	rm -rf *.a
	$(MAKE) -C $(ADI_PLATFORM_SRC) clean
	$(MAKE) -C $(ADI_COMMON_SRC) clean
