LIB_ADI_PLATFORM = libadi_platform.a
ADI_ADS8PLATFORM_SRC = ./ads8
ADI_ADS9PLATFORM_SRC = ./ads9
ADI_PLATFORM_UTILS_SRC = ./platform_utils

CC = aarch64-linux-gnu-gcc
ARFLAGS = -rv
CFLAGS = -Wall -Werror -I . -I platform_utils
EXT = c

SRC = ./adi_platform.$(EXT) \
	$(wildcard $(ADI_PLATFORM_UTILS_SRC)/*.$(EXT))
OBJS = $(SRC:.$(EXT)=.o)

all: ads8_platform_lib \
	ads9_platform_lib \
	$(LIB_ADI_PLATFORM)

.$(EXT).o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIB_ADI_PLATFORM): $(OBJS)
	ar $(ARFLAGS) $(LIB_ADI_PLATFORM) $(OBJS)

ads8_platform_lib:
	$(MAKE) -C $(ADI_ADS8PLATFORM_SRC)

ads9_platform_lib:
	$(MAKE) -C $(ADI_ADS9PLATFORM_SRC)
 
clean:
	rm -rf *.o
	rm -rf *.a
	$(MAKE) -C $(ADI_ADS8PLATFORM_SRC) clean
	$(MAKE) -C $(ADI_ADS9PLATFORM_SRC) clean
