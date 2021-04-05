/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:10:49 by mli               #+#    #+#             */
/*   Updated: 2019/10/18 12:10:14 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		s_len;
	char	*result;

	i = 0;
	if (!s || !f)
		return (0);
	s_len = (int)ft_strlen(s);
	if (!(result = (char *)ft_calloc(s_len + 1, sizeof(char))))
		return (NULL);
	while (i < s_len)
	{
		result[i] = f(i, s[i]);
		i++;
	}
	return (result);
}
