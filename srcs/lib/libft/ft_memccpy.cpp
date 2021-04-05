/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:19:33 by mli               #+#    #+#             */
/*   Updated: 2019/10/10 16:26:22 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*srcs;
	unsigned char	search;

	i = 0;
	dest = (unsigned char *)dst;
	srcs = (unsigned char *)src;
	search = (unsigned char)c;
	while (i < n)
	{
		dest[i] = srcs[i];
		if (srcs[i] == search)
			return ((void *)(&dest[i + 1]));
		i++;
	}
	return (NULL);
}
