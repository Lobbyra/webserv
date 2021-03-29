/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_server.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:19:02 by mli               #+#    #+#             */
/*   Updated: 2021/03/27 13:51:42 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_CLIENT_HPP
# define MINI_CLIENT_HPP

# include <iostream>
# include <string>
# include <unistd.h>

# include <sys/socket.h>
# include <netinet/in.h> // struct sockaddr_in
# include <arpa/inet.h> // inet_pton
# include <fcntl.h>
# include <sys/select.h>
# include <errno.h>

# include <list>

# include "./GNL/get_next_line.h"

typedef struct sockaddr t_sockaddr;
typedef struct sockaddr_in t_sockaddr_in;

void	ft_error(std::string const fct_name);
void	ft_sigint(int sig);
void	ft_signalhandler_enable(void);
void	ft_signalhandler_disable(void);

void	read_fd(const int &fd);
int		makeSocket(void);
void	ft_timeout_init(struct timeval *const time);

#endif // *********************************************** MINI_CLIENT_HPP end //
