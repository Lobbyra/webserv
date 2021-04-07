/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecaudal <jecaudal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 16:51:45 by mli               #+#    #+#             */
/*   Updated: 2021/04/07 14:09:43 by jecaudal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_HPP
# define LIB_HPP

# include <list>
# include <string>
# include <iostream>

# include "./libft/libft.h"
# include "./GNL/get_next_line.h"
# include "insert_stream_cont.hpp"

const std::string whitespaces("\t\n\v\f\r ");

std::string get_word_it(std::string::const_iterator it,
                        const std::string sep = whitespaces);

bool    is_space(char c);
bool    is_str_num(std::string str);

std::list<std::string> get_keys(void);

void    skip_it(std::string::const_iterator &it,
                const std::string sep = whitespaces);

template <typename it, typename T>
it  ft_find(it start, it end, T const &val) {
    while (start != end && *start != val)
        start++;
    return (start);
}

#endif // ******************************************************* LIB_HPP end //
