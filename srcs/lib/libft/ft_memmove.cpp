/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:32:25 by mli               #+#    #+#             */
/*   Updated: 2019/11/12 14:21:05 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*srcs;

	i = 0;
	dest = (unsigned char *)dst;
	srcs = (unsigned char *)src;
	if (dst < src)
		while (i < len)
		{
			dest[i] = srcs[i];
			i++;
		}
	else if (src < dst)
		while (len-- > 0)
			dest[len] = srcs[len];
	return (dst);
}
