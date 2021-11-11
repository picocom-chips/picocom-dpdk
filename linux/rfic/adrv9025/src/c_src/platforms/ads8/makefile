LIB_ADI_ADS8PLATFORM = libadi_ads8platform.a
CC = aarch64-linux-gnu-gcc
ARFLAGS = -rv
CFLAGS = -Wall -Werror -I. -I../
EXT = c

SRC = $(wildcard *.$(EXT))
OBJS = $(SRC:.$(EXT)=.o)

all: $(SRC) $(LIB_ADI_ADS8PLATFORM)

.$(EXT).o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIB_ADI_ADS8PLATFORM): $(OBJS)
	ar $(ARFLAGS) $(LIB_ADI_ADS8PLATFORM) $(OBJS)

clean:
	rm -rf *.o
	rm -rf *.a