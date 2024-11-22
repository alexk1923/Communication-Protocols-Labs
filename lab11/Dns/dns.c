// Protocoale de comunicatii
// Laborator 9 - DNS
// dns.c

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>


int usage(char* name)
{
	printf("Usage:\n\t%s -n <NAME>\n\t%s -a <IP>\n", name, name);
	return 1;
}

// Receives a name and prints IP addresses
void get_ip(char* name)
{
	int ret;
	struct addrinfo hints, *result, *p;

	memset(&hints, 0, sizeof(struct addrinfo));

	// TODO: set hints
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;



	ret =  getaddrinfo(name, NULL, &hints, &result);
	if(ret < 0) {
		printf("%s\n", gai_strerror(ret));
	}

	// TODO: get addresses
	
	p = result;
	while(p != NULL) {
		char ip[41];
		char *pr;
		if(p->ai_family == AF_INET) {
			pr = inet_ntop(AF_INET,  &(((struct sockaddr_in *)p->ai_addr)->sin_addr), ip, 40);
		} else {
			pr = inet_ntop(AF_INET6, &(((struct sockaddr_in *)p->ai_addr)->sin_addr), ip, 40);
		}
		printf("adresa:%s\n", pr);
		p = p->ai_next;
	}
	// TODO: iterate through addresses and print them

	// TODO: free allocated data
	free(result);
}

// Receives an address and prints the associated name and service
void get_name(char* ip)
{
	int ret;
	struct sockaddr_in *addr;
	char host[1024];
	char service[20];

	// inet_aton(ip, &addr.sin_addr);
	strcpy(service, "http");
	
	addr->sin_family = AF_INET;
	strcpy(host, ip);
	// TODO: fill in address data
	ret = getnameinfo(addr, sizeof(struct sockaddr_in), host, 1024, service, 20, NI_NUMERICSERV);

	if(ret < 0) {
		printf("%s\n", gai_strerror(ret));
	}
	// TODO: get name and service
	printf("host:%s\n", host);
	printf("service:%d\n", addr->sin_port);


	// TODO: print name and service
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		return usage(argv[0]);
	}

	if (strncmp(argv[1], "-n", 2) == 0) {
		get_ip(argv[2]);
	} else if (strncmp(argv[1], "-a", 2) == 0) {
		get_name(argv[2]);
	} else {
		return usage(argv[0]);
	}

	return 0;
}
