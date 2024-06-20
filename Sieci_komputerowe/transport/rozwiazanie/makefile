CC=gcc
CFLAGS= -std=gnu99 -Wall -Wextra

transport: transport.o send_udp.o receive_udp.o in_out_operations.o ip_operations.o sender_window.o
	$(CC) -o transport transport.o send_udp.o receive_udp.o in_out_operations.o ip_operations.o sender_window.o

clean:
	rm *.o

distclean:
	rm *.o transport
