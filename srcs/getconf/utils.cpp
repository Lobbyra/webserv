/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:57:41 by mli               #+#    #+#             */
/*   Updated: 2021/04/05 16:54:12 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "getconf.hpp"

void    check_curly_braces(const std::string &conf) {
    unsigned int lbrace = 0, rbrace = 0;
    std::string::const_iterator it = conf.begin(), ite = conf.end();

    for (; it != ite; ++it) {
        if (*it == '{')
            ++lbrace;
        else if (*it == '}')
            ++rbrace;
    }
    if (lbrace != rbrace)
        throw std::logic_error("GetConfig: Braces does not match");
}
