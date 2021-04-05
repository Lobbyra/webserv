/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 16:51:45 by mli               #+#    #+#             */
/*   Updated: 2021/04/05 17:02:35 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_HPP
# define LIB_HPP

# include <iostream>
# include <string>

# include "./libft/libft.h"
# include "./GNL/get_next_line.h"

const std::string whitespaces("\t\n\v\f\r ");

std::string get_word_it(std::string::const_iterator it,
                        const std::string sep = whitespaces);

#endif // ******************************************************* LIB_HPP end //
