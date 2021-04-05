/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 16:54:25 by mli               #+#    #+#             */
/*   Updated: 2021/04/05 16:54:43 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.hpp"

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
