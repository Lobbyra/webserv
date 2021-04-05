/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:27:59 by mli               #+#    #+#             */
/*   Updated: 2019/10/11 15:23:01 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*newcpy;
	size_t	src_len;

	src_len = ft_strlen(s1);
	if ((newcpy = (char *)ft_calloc(src_len + 1, sizeof(*newcpy))) == NULL)
		return (NULL);
	return (ft_memcpy(newcpy, s1, src_len));
}
