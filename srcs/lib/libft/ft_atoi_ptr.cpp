/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ptr.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:14:46 by mli               #+#    #+#             */
/*   Updated: 2021/04/02 13:43:06 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi_ptr(const char *str, int *i, bool handle_sign = true)
{
	int signe;
	int result;

	signe = 1;
	result = 0;
	while (str[*i] == '\t' || str[*i] == '\n' || str[*i] == '\v' ||
			str[*i] == '\f' || str[*i] == '\r' || str[*i] == ' ')
		(*i)++;
	if (handle_sign) {
		if (str[*i] == '+')
			(*i)++;
		else if (str[*i] == '-')
		{
			signe = -1;
			(*i)++;
		}
	}
	while (str[*i] >= '0' && str[*i] <= '9')
		result = (10 * result) + str[(*i)++] - '0';
	return (result * signe);
}
