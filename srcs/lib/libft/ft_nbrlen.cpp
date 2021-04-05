/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 14:45:12 by mli               #+#    #+#             */
/*   Updated: 2020/03/14 16:04:46 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_nbrlen_base(long int nb, int base_len)
{
	int size;

	size = 0;
	if (nb <= 0)
		size++;
	while (nb != 0)
	{
		nb /= base_len;
		size++;
	}
	return (size);
}

int		ft_nbrlen(long int nb)
{
	return (ft_nbrlen_base(nb, 10));
}
