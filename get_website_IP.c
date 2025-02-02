#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("\nUso: './get_website_IP [URL]'");
		return 1;
	}

	char *hostname = argv[1];
	struct addrinfo hints, *res;

	//Configura as opções para getaddrinfo
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	//Pega o IP do hostname
	int s = getaddrinfo(hostname, NULL, &hints, &res);
	if(s != 0)
	{
		printf("\nErro ao pegar o IP\n");
		return 1;
	}

	//Percorre a lista de IPs
	for(struct addrinfo *p = res ; p != NULL ; p = p->ai_next)
	{
		struct sockaddr_in *addr = (struct sockaddr_in *)p->ai_addr;
		printf("\nIP: %s", inet_ntoa(addr->sin_addr));
	}

	//Libera a lista de IPs
	freeaddrinfo(res);
	return 0;
}
