/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereligi <jereligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:06:47 by jereligi          #+#    #+#             */
/*   Updated: 2021/04/08 15:02:25 by jereligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_serv.hpp"

/* Mini-Serv
1 - init socket
2 - bind
3 - listen
4 - accept
5 - get respons of client
6 - send respons to client
*/



int			main(void)
{
	int listensock, client_sock = 0;
	struct sockaddr_in	serv_addr;
	char respons[] = "HTTP/1.1 200 OK\r\n\r\n Congraculation !";

	if ((listensock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "error: Socket creation" << std::endl;
		return -1;
	}

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(18000);

	if ((bind(listensock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
	{
		std::cerr << "error: Socket bind" << std::endl;
		return -1;		
	}

	if ((listen(listensock, 10)) < 0)
	{
		std::cerr << "error: Socket listen" << std::endl;
		return -1;			
	}

	while (true)
	{
		int		n = 0;
		char	*line;

		std::cout << "Wait for connection on the port ..." << std::endl;
		if ((client_sock = accept(listensock, NULL, NULL)) == -1)
		{
			std::cerr << "error: Socket accept" << std::endl;
			return -1;	
		}
		std::cout << "New client ..." << std::endl;
	
		while ((n = get_next_line(client_sock, &line)) == 1) 
		{
			std::cout << line << std::endl;
			free(line);
		}
		if (n == 0) {
			free(line);
		}
		if (send(client_sock , respons, strlen(respons) , 0 ) == -1)
		{
			std::cerr << "error: Respons to client" << std::endl;
			return -1;	
		}
		close(client_sock);
	}
	return (0);
}