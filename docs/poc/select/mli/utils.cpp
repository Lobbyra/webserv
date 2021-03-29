/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:37:57 by mli               #+#    #+#             */
/*   Updated: 2021/03/29 14:57:03 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_server.hpp"

std::list<int> g_sockets;

void	ft_error(std::string const fct_name) {
	std::cout << fct_name << ": " << strerror(errno) << std::endl;
	exit(1);
}

void	ft_sigint(int sig) {
	int fd;
	int opt = 1;

	(void)sig;
	while (g_sockets.size() != 0) {
		fd = g_sockets.front();

		if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
			ft_error("setsockopt");
		close(fd);
		g_sockets.pop_front();
	}
	std::cout << "\r[SIGINT] All sockets are closed." << std::endl;
	exit(0);
}

void	ft_signalhandler_enable(void) {
	signal(SIGINT, ft_sigint);
}

void	ft_signalhandler_disable(void) {
	signal(SIGINT, SIG_DFL);
}

void	read_fd(const int &fd) {
	int		n;
	char	*line;

	while ((n = get_next_line(fd, &line)) == 1) {
		std::cout << line << std::endl;
		free(line);
	}
	if (n == 0)
		free(line);
	else if (n == -1)
		ft_error("GNL");
}

int		makeSocket(void) {
	int newSocket;

	if ((newSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ft_error("socket");
	g_sockets.push_back(newSocket);
	return (newSocket);
}

void	ft_timeout_init(struct timeval *const time) {
	bzero(time, sizeof(*time));
	time->tv_sec = 1;
}
