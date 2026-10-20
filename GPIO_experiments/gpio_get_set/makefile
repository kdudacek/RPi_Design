CC=gcc
CFLAGS=

INCLUDES=-I.

HEADERS=gpio_get_set.h gpio_utils.h trace.h config.h

gpio_get_set: gpio_get_set.o gpio_utils.o trace.o
	$(CC) $(LIBS) $(CFLAGS) -o gpio_get_set gpio_get_set.o gpio_utils.o trace.o

gpio_get_set.o: gpio_get_set.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c gpio_get_set.c

gpio_utils.o: gpio_utils.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c gpio_utils.c

trace.o: trace.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c trace.c

