/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:04:54 by mli               #+#    #+#             */
/*   Updated: 2021/05/20 16:55:24 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char				*dest = (unsigned char *)b;
	unsigned char const *const	end = dest + len;
	const unsigned char			src = c;

	while (dest != end)
		*dest++ = src;
	return (b);
}
