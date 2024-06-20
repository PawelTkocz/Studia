CC=gcc
CFLAGS= -std=gnu99 -Wall -Wextra

webserver: webserver.o serve_client.o send_response.o get_request.o
	$(CC) -o webserver webserver.o serve_client.o send_response.o get_request.o

clean:
	rm *.o

distclean:
	rm *.o webserver
