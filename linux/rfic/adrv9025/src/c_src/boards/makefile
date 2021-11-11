LIB_ADI_BOARDS = libadi_boards.a

ADI_MOTHERBOARD_SRC = ./daughterboards
ADI_DAUGHTERBOARD_SRC = ./motherboards
ADI_PLATFORM_SRC = ../platforms
ADI_COMMON_SRC = ../common
ADI_COMMON_ERROR_SRC = ../common/adi_error
ADI_COMMON_LOGGING_SRC = ../common/adi_logging
ADI_COMMON_HAL_SRC = ../common/adi_hal
ADI_FPGA9025_SRC = ../devices/fpga9025
ADI_FPGA9010_SRC = ../devices/fpga9010
ADI_AD9528_SRC = ../devices/ad9528
ADI_ADRV9025_SRC = ../devices/adrv9025

ARFLAGS = -rv

all: 	adi_platform_lib \
	adi_common_lib \
	adi_fpga9025_lib \
	adi_fpga9010_lib \
	adi_ad9528_lib \
	adi_adrv9025_lib \
	motherboard_lib \
	daughterboard_lib \
	$(LIB_ADI_BOARDS)

$(LIB_ADI_BOARDS): $(OBJS)
	ar $(ARFLAGS) $(LIB_ADI_BOARDS)

motherboard_lib:
	$(MAKE) -C $(ADI_MOTHERBOARD_SRC)

daughterboard_lib:
	$(MAKE) -C $(ADI_DAUGHTERBOARD_SRC)

adi_platform_lib:
	$(MAKE) -C $(ADI_PLATFORM_SRC)

adi_common_lib:
	$(MAKE) -C $(ADI_COMMON_SRC)

adi_fpga9025_lib:
	$(MAKE) -C $(ADI_FPGA9025_SRC)
 
adi_fpga9010_lib:
	$(MAKE) -C $(ADI_FPGA9010_SRC)
 
adi_ad9528_lib:
	$(MAKE) -C $(ADI_AD9528_SRC)

adi_adrv9025_lib:
	$(MAKE) -C $(ADI_ADRV9025_SRC)
 
clean:
	rm -rf *.o
	rm -rf *.a
	$(MAKE) -C $(ADI_MOTHERBOARD_SRC) clean
	$(MAKE) -C $(ADI_DAUGHTERBOARD_SRC) clean
	$(MAKE) -C $(ADI_PLATFORM_SRC) clean
	$(MAKE) -C $(ADI_COMMON_SRC) clean
	$(MAKE) -C $(ADI_FPGA9025_SRC) clean
	$(MAKE) -C $(ADI_FPGA9010_SRC) clean
	$(MAKE) -C $(ADI_AD9528_SRC) clean
	$(MAKE) -C $(ADI_ADRV9025_SRC) clean
