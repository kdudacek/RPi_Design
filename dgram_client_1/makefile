CC=gcc
CFLAGS=

INCLUDES=-I.

HEADERS=dgram_client_main.h dgram_client.h trace.h commands.h config.h

dgram_client: dgram_client_main.o dgram_client.o trace.o
	$(CC) $(LIBS) $(CFLAGS) -o dgram_client dgram_client_main.o dgram_client.o trace.o

dgram_client_main.o: dgram_client_main.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c dgram_client_main.c

dgram_client.o: dgram_client.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c dgram_client.c

trace.o: trace.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c trace.c

