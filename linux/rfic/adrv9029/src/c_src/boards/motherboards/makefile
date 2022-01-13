LIBADI_MOTHERBOARD = libadi_motherboard.a
CC = aarch64-linux-gnu-gcc
ARFLAGS = -rv
CFLAGS = -Wall -Werror -I ../daughterboards -I ../../platforms -I ../../platforms/platform_utils -I ../../common/  -I ../../common/adi_error -I ../../common/adi_logging -I../../common/adi_hal
EXT = c

SRC = $(wildcard *.$(EXT))

OBJS = $(SRC:.$(EXT)=.o)

all: $(SRC) $(LIBADI_MOTHERBOARD)

.$(EXT).o:
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBADI_MOTHERBOARD): $(OBJS)
	ar $(ARFLAGS) $(LIBADI_MOTHERBOARD) $(OBJS)

clean:
	rm -rf *.o
	rm -rf *.a
