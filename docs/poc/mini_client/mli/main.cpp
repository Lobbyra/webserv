/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:18:55 by mli               #+#    #+#             */
/*   Updated: 2021/03/22 15:31:41 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_client.hpp"

bool	usage_error(char *str)
{
	std::cout << "Usage:\t" << str << " <IP> <PORT>" << std::endl;
	return (1);
}

void	ft_client(char **argv)
{
	int		sockfd;
	struct sockaddr_in servaddr;
	const std::string msg = "GET / HTTP/1.1\nHost: example.com\r\n\r\n";
	const int msg_len = strlen(msg.c_str());

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ft_error("socket");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		ft_error("inet_pton");

	if (connect(sockfd, (t_sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		ft_error("connect");

	if (write(sockfd, msg.c_str(), msg_len) != msg_len)
		ft_error("write");

	char	*line;
	int		n;
	while ((n = get_next_line(sockfd, &line)) == 1) {
		std::cout << line << std::endl;
		free(line);
	}
	if (n == 0) {
		free(line);
	}
	exit(0);
}

int		main(int argc, char **argv)
{
	if (argc != 3)
		return (usage_error(argv[0]));
	ft_client(argv);
	return (0);
}
