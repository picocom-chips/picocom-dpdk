LIB_ADI_COMMON = libadi_common.a
CC = aarch64-linux-gnu-gcc
ADI_COMMON_SRC = ./
ADI_COMMON_ERROR_SRC = ./adi_error/
ADI_COMMON_LOGGING_SRC = ./adi_logging/
ADI_COMMON_HAL_SRC = ./adi_hal/

ARFLAGS = -rv
CFLAGS = -Wall -Werror -I../platforms/ -I./  -I./adi_error/ -I./adi_logging/ -I./adi_hal/ 
EXT = c

SRC = $(wildcard $(ADI_COMMON_SRC)/*.$(EXT)) \
	$(wildcard $(ADI_COMMON_ERROR_SRC)/*.$(EXT)) \
	$(wildcard $(ADI_COMMON_LOGGING_SRC)/*.$(EXT)) \
	$(wildcard $(ADI_COMMON_HAL_SRC)/*.$(EXT))

OBJS = $(SRC:.$(EXT)=.o)

all: $(SRC) $(LIB_ADI_COMMON)

.$(EXT).o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIB_ADI_COMMON): $(OBJS)
	ar $(ARFLAGS) $(LIB_ADI_COMMON) $(OBJS)

clean:
	rm -rf $(ADI_COMMON_SRC)/*.o
	rm -rf *.a

