/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_client.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereligi <jereligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:03:56 by jereligi          #+#    #+#             */
/*   Updated: 2021/04/07 17:36:38 by jereligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

/*
1 - init socket
2 - connect socket
3 - send header
4 - receive anwser
*/

/*
** structure sockaddr_in
**
** .sin_addr.s_addr : qui définit l'adresse du serveur.
**
** .sin_family : la « famille » du socket, le type si on veut. Pour Internet, les programmeurs utilisent généralement AF_INET.
**
** .sin_port : le port sur lequel vous voulez vous connecter ou bien écouter. htons(server_port)
*/

// int socket(int domain, int type, int protocol);  


int		main(int ac, char **av)
{
	int sock = 0;
	struct sockaddr_in	serv_addr;
	
	if (ac != 2)
	{
		std::cout << "usage: mini_client [ip]" << std::endl;
		return 0;
	}
		
	// init socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
		std::cerr << "error: Socket creation" << std::endl;
		return -1;
    }

	// convertir des adresses IPv4 et IPv6 sous forme texte en forme binaire
	// int inet_pton(int af, const char *src, void *dst);
	if (inet_pton(AF_INET, av[1], &serv_addr.sin_addr) < 0)
	{
		std::cerr << "error: inet_pton address ip" << std::endl;
		return -1;
	}

	serv_addr.sin_port = htons(80);
	serv_addr.sin_family = AF_INET;

	// connect socket
	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cerr << "error: Socket connect" << std::endl;
        return -1;
	}
	std::cout << "CONNECTED !" << std::endl;

	// create request
	// char request[4096] = "GET HTTP/1.1\r\n\r\n";
	char request[4096] = "GET https://example.com/ HTTP/1.1\r\n\r\n";
	// char request[4096] = "GET / HTTP/1.1\nHost: example.com\r\n\r\n";

	// send
    if (write(sock, request, strlen(request)) != (long)strlen(request))
	{
        std::cerr << "error: Socket send request" << std::endl;
        return -1;
    }

	int		n;
	char	recvline[4096];
	while ((n = read(sock, recvline, 4095)) > 0)
	{
		printf("%s", recvline);
	}
    return 0;
}