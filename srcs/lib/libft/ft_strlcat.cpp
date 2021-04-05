/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:09:57 by mli               #+#    #+#             */
/*   Updated: 2019/10/08 18:08:17 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;
	size_t to_return;

	i = 0;
	j = 0;
	to_return = 0;
	while (dst[to_return] && (to_return < dstsize))
		to_return++;
	while (src[i])
	{
		if (dstsize > 0)
			if (to_return + i < dstsize - 1)
				dst[to_return + (j++)] = src[i];
		i++;
	}
	if (dstsize > 0 && to_return < dstsize)
		dst[to_return + j] = '\0';
	return (to_return + i);
}
