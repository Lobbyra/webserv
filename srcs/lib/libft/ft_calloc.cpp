/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 17:53:51 by mli               #+#    #+#             */
/*   Updated: 2019/10/12 17:48:44 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			total_len;
	unsigned char	*result;

	total_len = count * size;
	if (!(result = (unsigned char *)malloc(sizeof(*result) * total_len)))
		return (NULL);
	ft_bzero(result, total_len);
	return (result);
}
