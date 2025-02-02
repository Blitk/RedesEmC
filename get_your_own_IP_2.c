#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	char hostname[1024];
	struct hostent *he;
	struct in_addr **addr_list;

	//Pega o hostname do sistema
	gethostname(hostname, 1024);

	//Pega o IP do Hostname
	he = gethostbyname(hostname);
	if(he == NULL)
	{
		printf("\nErro ao pegar o IP\n");
		return 1;
	}

	addr_list = (struct in_addr**)he->h_addr_list;
	printf("\nIP: %s", inet_ntoa(*addr_list[0]));

	return 0;
}