/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_client.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:19:02 by mli               #+#    #+#             */
/*   Updated: 2021/03/22 14:49:42 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_CLIENT_HPP
# define MINI_CLIENT_HPP

# include <iostream>
# include <string>

# include <sys/socket.h>
# include <netinet/in.h> // struct sockaddr_in
# include <arpa/inet.h> // inet_pton
# include <unistd.h>
# include <errno.h>

# include "./GNL/get_next_line.h"

typedef struct sockaddr t_sockaddr;

# define SERVER_PORT 80

void	ft_error(std::string const fct_name);

#endif // *********************************************** MINI_CLIENT_HPP end //
