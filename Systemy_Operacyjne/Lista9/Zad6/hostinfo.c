#include "csapp.h"

int main(int argc, char **argv) {
  struct addrinfo *p, *listp, hints;
  char buf[MAXLINE];
  //analogicznie dla service
  char srv[MAXLINE];
  int rc, flags;

  //wprowadzam dwie zmienne
  const char *domain;
  const char *service;

  if(argc == 2){
	domain = argv[1];
	service = NULL;
  }
  else if(argc == 3){
	domain = argv[1];
	service = argv[2];
  }
  else{
	app_error("usage: %s <domain name> <optionally service>\n", argv[0]);
  }


  /* Get a list of addrinfo records */
  memset(&hints, 0, sizeof(struct addrinfo));

  //hints.ai_family = AF_INET; /* IPv4 only */
  hints.ai_family = AF_UNSPEC;
  //zmiana na AF_UNSPEC aby obslugiwac tez Ipv6

  hints.ai_socktype = SOCK_STREAM;
  //hints.ai_socktype = 0;
  //zmiana aby obslugiwac tftp

  /* Connections only */
  //if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0)
  if ((rc = getaddrinfo(domain, service, &hints, &listp)) != 0)
    gai_error(rc, "getaddrinfo");
  //zamiana NULL na service aby pobrac informacje o service

  /* Walk the list and display each IP address */
  //flags = NI_NUMERICHOST; /* Display address string instead of domain name */
  flags = NI_NUMERICHOST | NI_NUMERICSERV;
  for (p = listp; p; p = p->ai_next) {
    //Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
    Getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, srv, MAXLINE, flags);
    if(service && p->ai_family == AF_INET6)
	printf("[%s]:%s\n", buf, srv);
    else if(service)
	printf("%s:%s\n", buf, srv);
    else
	printf("%s\n", buf);
  }

  /* Clean up */
  freeaddrinfo(listp);

  return EXIT_SUCCESS;
}
