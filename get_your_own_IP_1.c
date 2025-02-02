#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ifaddrs.h>

int main()
{
	struct ifaddrs *ifaddr;
	struct ifaddrs *ifa;
	int family;
	int s;
	char host[NI_MAXHOST];

	//Pega as informações de rede
	if(getifaddrs(&ifaddr) == -1 )
	{
		printf("\nErro ao pegar as informações da rede\n");
		return 1;
	}

	//Percorre as interfaces de rede
	for(ifa = ifaddr ; ifa != NULL ; ifa = ifa->ifa_next)
	{
		if(ifa->ifa_addr == NULL)
		{
			continue;
		}
		family = ifa->ifa_addr->sa_family;

		//verifica se a interface é IPv4 ou IPv6
		if(family == AF_INET || family == AF_INET6)
		{
			s = getnameinfo(ifa->ifa_addr, (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

			if(s != 0)
			{
				printf("\nErro ao pegar o IP\n");
				return 1;
			}
			printf("\nIP: %s\n", host);
		}
	}

	//libera as informações de rede
	freeifaddrs(ifaddr);
	return 0;
	
}