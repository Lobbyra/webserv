/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:15:40 by mli               #+#    #+#             */
/*   Updated: 2019/10/18 12:08:25 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_to_trim(char to_test, char const *set)
{
	int i;

	i = -1;
	while (set[++i])
		if (set[i] == to_test)
			return (1);
	return (0);
}

static int	ft_size(char const *s1, char const *set)
{
	int	i;
	int	max;

	i = 0;
	max = (int)ft_strlen(s1) - 1;
	while (s1[max] && is_to_trim(s1[max], set))
		max--;
	while (i <= max)
		i++;
	return (i);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		size;
	char	*result;

	i = 0;
	j = 0;
	size = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && is_to_trim(s1[i], set))
		i++;
	if (s1[i])
		size = ft_size(&s1[i], set);
	if (!(result = (char *)ft_calloc(size + 1, sizeof(char))))
		return (NULL);
	while (s1[i] && j < size)
		result[j++] = s1[i++];
	return (result);
}
