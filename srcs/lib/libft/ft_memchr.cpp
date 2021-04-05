/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:29:10 by mli               #+#    #+#             */
/*   Updated: 2019/10/10 16:22:35 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	searched;

	i = 0;
	str = (unsigned char *)s;
	searched = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == searched)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
