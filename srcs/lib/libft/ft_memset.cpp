/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:04:54 by mli               #+#    #+#             */
/*   Updated: 2019/10/08 16:09:37 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	src;

	i = 0;
	dest = (unsigned char *)b;
	src = (unsigned char)c;
	while (i < len)
		dest[i++] = src;
	return (b);
}
