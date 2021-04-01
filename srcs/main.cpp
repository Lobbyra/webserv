/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 12:21:29 by mli               #+#    #+#             */
/*   Updated: 2021/03/30 15:19:41 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

static int	print_usage(char *prog_name) {
	std::cerr << "Usage: " << prog_name << " <nginx.conf>" << std::endl;
	return (1);
}

int		main(int argc, char **argv) {
	if (argc != 2)
		return (print_usage(argv[0]));
	std::cout << get_str_conf(argv[1]) << std::endl;
	return (0);
}
