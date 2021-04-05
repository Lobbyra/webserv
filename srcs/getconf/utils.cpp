/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:57:41 by mli               #+#    #+#             */
/*   Updated: 2021/04/02 16:43:19 by mli              ###   ########.fr       */
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

std::string get_word_it(std::string::const_iterator it, std::string const sep) {
    std::string::const_iterator ite = it;

    while (sep.find(*ite) == std::string::npos)
        ++ite;
    return (std::string(it, ite));
}

/*
int		main(void)
{
    std::string str = "lol mdrxd qweqwe";
    std::string::iterator it;

    it = str.begin();
    std::cout << get_word_it(it) << std::endl;

    it = it + 3;
    std::cout << get_word_it(it) << std::endl;

    ++it;
    std::cout << get_word_it(it) << std::endl;
    return (0);
}
*/
