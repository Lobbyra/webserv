/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:18:55 by mli               #+#    #+#             */
/*   Updated: 2021/03/27 15:02:03 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_server.hpp"

void	ft_server(int target_port)
{
	int		listenfd;
	t_sockaddr_in servaddr;
	const std::string resp = "HTTP/1.1 200 OK\r\n\r\nGot The Message! :o";
	const int resp_len = strlen(resp.c_str());

	listenfd = makeSocket();
	fcntl(listenfd, F_SETFL, O_NONBLOCK);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(target_port);

	if ((bind(listenfd, (t_sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		ft_error("bind");
	if ((listen(listenfd, 10)) < 0)
		ft_error("listen");

	std::cout << "Waiting connection on port: " << target_port << std::endl;
	while (true) {
		int		connfd;
		fd_set	fdset;
		struct timeval time;

		FD_ZERO(&fdset); FD_SET(listenfd, &fdset);
		ft_timeout_init(&time);
		select(listenfd + 1, &fdset, NULL, NULL, &time);
		if (errno == EAGAIN || !FD_ISSET(listenfd, &fdset)) {
			std::cout << "No connection yet..." << std::endl;
			continue ;
		}
		else if (errno != 0)
			ft_error("select");
		connfd = accept(listenfd, NULL, NULL);
		if (errno != 0)
			ft_error("accept");
		std::cout << "Oh! Message received..." << std::endl;

		/*
		read_fd(connfd);
		if (write(connfd, resp.c_str(), resp_len) != resp_len)
			ft_error("write");
		*/
		close(connfd);
	}
	(void)resp_len;
}

char SERVER_PORT[] = "18000";

bool	usage_error(char *str)
{
	std::cout << "Usage:\n" << \
		str << " <PORT=" << SERVER_PORT << ">" << std::endl;
	return (1);
}

int		main(int argc, char **argv)
{
	if (argc == 1)
		argv[argc++] = SERVER_PORT;
	else if (argc != 2)
		return (usage_error(argv[0]));
	ft_signalhandler_enable();
	ft_server(atoi(argv[1]));
	return (0);
}
