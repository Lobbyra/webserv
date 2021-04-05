/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:32:36 by mli               #+#    #+#             */
/*   Updated: 2019/10/10 16:30:30 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	size_t			s_len;
	char			*to_return;
	unsigned char	searched;

	to_return = NULL;
	s_len = ft_strlen(s);
	searched = (unsigned char)c;
	i = 0;
	while (i <= s_len)
	{
		if (s[i] == searched)
			to_return = (char *)(&(s[i]));
		i++;
	}
	return (to_return);
}
