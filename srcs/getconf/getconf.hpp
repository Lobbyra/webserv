/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getconf.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:49:14 by mli               #+#    #+#             */
/*   Updated: 2021/04/05 11:52:09 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETCONF_HPP
# define GETCONF_HPP

# include "../webserv.hpp"

const std::string whitespaces("\t\n\v\f\r ");

void        check_curly_braces(const std::string &conf);
std::string get_word_it(std::string::const_iterator it,
                        const std::string sep = whitespaces);

#endif // *************************************************** GETCONF_HPP end //
