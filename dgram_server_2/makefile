CC=gcc
CFLAGS=

INCLUDES=-I.

HEADERS=dgram_server_main.h dgram_server.h gpio_utils.h trace.h

dgram_server: dgram_server_main.o dgram_server.o gpio_utils.o trace.o
	$(CC) $(LIBS) $(CFLAGS) -o dgram_server dgram_server_main.o dgram_server.o gpio_utils.o trace.o

dgram_server_main.o: dgram_server_main.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c dgram_server_main.c

dgram_server.o: dgram_server.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c dgram_server.c

gpio_utils.o: gpio_utils.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c gpio_utils.c

trace.o: trace.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c trace.c

