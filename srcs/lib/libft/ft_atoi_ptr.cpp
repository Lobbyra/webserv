/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ptr.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:14:46 by mli               #+#    #+#             */
/*   Updated: 2021/04/06 12:06:25 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_atoi_ptr:
 *
 * str: string to be parsed
 * i: address of the index to be incremented
 * h_sign = true: bool to handle sign or not
 * h_space = true: bool to handle whitespaces or not
 */

int		ft_atoi_ptr(const char *str, int *i, bool h_sign, bool h_space)
{
	int signe = 1;
	int result = 0;

	if (h_space)
		while (str[*i] == '\t' || str[*i] == '\n' || str[*i] == '\v' ||
				str[*i] == '\f' || str[*i] == '\r' || str[*i] == ' ')
			(*i)++;
	if (h_sign) {
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
