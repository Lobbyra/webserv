/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:18:55 by mli               #+#    #+#             */
/*   Updated: 2021/03/23 16:29:10 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_server.hpp"

void	read_fd(const int &fd) {
	int		n;
	char	*line;

	while ((n = get_next_line(fd, &line)) == 1) {
		std::cout << line << std::endl;
		free(line);
	}
	if (n == 0) {
		free(line);
	}
}

void	ft_server(int target_port)
{
	int		listenfd;
	struct sockaddr_in servaddr;
	const std::string resp = "HTTP/1.1 200 OK\r\n\r\nGot The Message! :o";
	const int resp_len = strlen(resp.c_str());

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ft_error("socket");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(target_port);

	if ((bind(listenfd, (sockaddr *)&servaddr, sizeof(servaddr))) < 0)
		ft_error("bind");
	if ((listen(listenfd, 10)) < 0)
		ft_error("listen");

	while (true) {
		int		connfd;

		std::cout << "Waiting connection on port: " << target_port << std::endl;
		connfd = accept(listenfd, NULL, NULL);
		read_fd(connfd);

		if (write(connfd, resp.c_str(), resp_len) != resp_len)
			ft_error("write");
		close(connfd);
	}
	exit(0);
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
	ft_server(atoi(argv[1]));
	return (0);
}
