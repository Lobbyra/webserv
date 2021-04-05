/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:02:08 by mli               #+#    #+#             */
/*   Updated: 2019/10/18 12:07:00 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newcpy;
	size_t	i;
	size_t	s_len;

	i = 0;
	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if ((newcpy = (char *)ft_calloc(len + 1, sizeof(*newcpy))) == NULL)
		return (NULL);
	if (start < s_len)
		while (i < len && s[start])
			newcpy[i++] = s[start++];
	return (newcpy);
}
