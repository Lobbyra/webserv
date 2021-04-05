/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:29:58 by mli               #+#    #+#             */
/*   Updated: 2019/10/18 10:44:11 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		i;
	size_t		s_len;
	char		searched;

	s_len = ft_strlen(s);
	searched = (char)c;
	i = 0;
	while (i <= s_len)
	{
		if (s[i] == searched)
			return ((char *)&(s[i]));
		i++;
	}
	return (NULL);
}
