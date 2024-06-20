CC=gcc
CFLAGS= -std=gnu99 -Wall -Wextra

router: router.o send_udp.o receive_udp.o in_out_operations.o ip_operations.o
	$(CC) -o router router.o send_udp.o receive_udp.o in_out_operations.o ip_operations.o

clean:
	rm *.o

distclean:
	rm *.o router
