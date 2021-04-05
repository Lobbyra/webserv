/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:04:54 by mli               #+#    #+#             */
/*   Updated: 2021/04/05 16:56:11 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <string>
# include <exception>
# include <fcntl.h>

# include "./lib/lib.hpp"

std::string get_str_conf(const char *const path);

#endif // ****************************************************** MAIN_HPP end //
