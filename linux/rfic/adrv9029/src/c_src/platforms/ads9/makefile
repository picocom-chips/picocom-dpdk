LIB_ADI_ADS9PLATFORM = libadi_ads9platform.a
CC = aarch64-linux-gnu-gcc
ARFLAGS = -rv
CFLAGS = -Wall -Werror -I. -I../
EXT = c

SRC = $(wildcard *.$(EXT))
OBJS = $(SRC:.$(EXT)=.o)

all: $(SRC) $(LIB_ADI_ADS9PLATFORM)

.$(EXT).o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIB_ADI_ADS9PLATFORM): $(OBJS)
	ar $(ARFLAGS) $(LIB_ADI_ADS9PLATFORM) $(OBJS)

clean:
	rm -rf *.o
	rm -rf *.a