CC=gcc
CFLAGS= -std=gnu99 -Wall -Wextra

traceroute: traceroute.o in_out_operations.o send_packet.o receive_packet.o
	$(CC) -o traceroute traceroute.o in_out_operations.o send_packet.o receive_packet.o

clean:
	rm *.o

distclean:
	rm *.o traceroute
