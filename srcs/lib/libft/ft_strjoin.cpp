/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 13:06:58 by mli               #+#    #+#             */
/*   Updated: 2019/10/18 12:08:48 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	size_t	tt_len;
	char	*string;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	tt_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(string = (char *)malloc(sizeof(*string) * tt_len)))
		return (NULL);
	while (*s1)
		string[i++] = *(s1++);
	while (*s2)
		string[i++] = *(s2++);
	string[i] = '\0';
	return (string);
}
