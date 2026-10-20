CC=gcc
CFLAGS=

INCLUDES=-I.

HEADERS=hw_set_set.h gpio_utils.h trace.h config.h

hw_set_set: hw_set_set.o gpio_utils.o trace.o
	$(CC) $(LIBS) $(CFLAGS) -o hw_set_set hw_set_set.o gpio_utils.o trace.o

hw_set_set.o: hw_set_set.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c hw_set_set.c

gpio_utils.o: gpio_utils.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c gpio_utils.c

trace.o: trace.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c trace.c

