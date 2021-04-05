/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_serv_value.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 11:04:15 by mli               #+#    #+#             */
/*   Updated: 2021/04/05 14:58:15 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "getconf.hpp"

void    parse_client_max_body_size(std::string::const_iterator it, void *ptr) {
    int i = 0;
    int *const data = reinterpret_cast<int *>(ptr);
    const char *str = get_word_it(++it).c_str();

    if (!ft_isdigit(str[i]))
        throw std::logic_error("Invalid client_max_body_size");
    *data = ft_atoi_ptr(str, &i, 0);
    if (str[i] == 'k')
        *data *= 1000;
    else if (str[i] == 'm')
        *data *= 1000000;
    else
        --i;
    ++i;
    if (str[i] != ';')
        throw std::logic_error("Invalid client_max_body_size");
}

/*
int		main(void)
{
    int res;
    std::string str = " 20m;";
    //str = " m;";

    parse_client_max_body_size(str.begin(), &res);
    std::cout << "res is: " << res << std::endl;
    return (0);
}
*/

void    parse_root(std::string::const_iterator it, void *ptr) {
    std::string *const data = reinterpret_cast<std::string *>(ptr);

    *data = get_word_it(++it).c_str();
    if (data->size() <= 1 || data->back() != ';')
        throw std::logic_error("Invalid root");
    data->erase(--data->end());
}

/*
int		main(void)
{
    std::string res;
    std::string str = " path/to/file; other_key other_value;";

    //str = " path/to/file ; other_key other_value;";
    //str = " path/to/file other_key other_value;";
    //str = " ;";

    try {
        parse_root(str.begin(), &res);
    }
    catch(const std::exception &e) {
        std::cerr << "CATCH EXCEPTION: " << e.what() << '\n';
        res = "empty";
    }
    std::cout << "res is: |" << res << "|" << std::endl;
}
*/
