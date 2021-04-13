/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereligi <jereligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:26:55 by jereligi          #+#    #+#             */
/*   Updated: 2021/04/08 17:57:09 by jereligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//  fcntl |  FD_ZERO | FD_SET | FD_ISSET

#include "select.hpp"

int		main(void)
{
	int					listenfd, clientfd;
	struct sockaddr_in	serv_addr;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "error: Socket creation" << std::endl;
		return -1;
	}

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(18000);
	serv_addr.sin_family = AF_INET;

	// modify fd no-block
	fcntl(listenfd, F_SETFL, O_NONBLOCK);

	if ((bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
	{
		std::cerr << "error: Socket bind" << std::endl;
		return -1;		
	}

	if ((listen(listenfd, 10)) < 0)
	{
		std::cerr << "error: Socket listen" << std::endl;
		return -1;			
	}

	// init fd_set
	fd_set              set;
    struct timeval      time;
	char respons[] = "HTTP/1.1 200 OK\r\n\r\n Congraculation !";

	time.tv_sec = 1;
	time.tv_usec = 0;

	FD_ZERO(&set);
	while (true)
	{
		FD_SET(listenfd, &set);
		select(listenfd + 1, &set, NULL, NULL, &time);
		if (FD_ISSET(listenfd, &set))
		{
			if ((clientfd = accept(listenfd, NULL, NULL)) < 0)
			{
				std::cerr << "error: Socket accept" << std::endl;	
			}
			std::cout << "Toc toc ! Client here !" << std::endl;
			if (send(clientfd , respons, strlen(respons) , 0 ) == -1)
			{
				std::cerr << "error: Respons to client" << std::endl;
				return -1;	
			}
			close(clientfd);
		}
		else
		{
			std::cout << "silence" << std::endl;
		}
		FD_CLR(listenfd, &set);
	}

	return (0);
}