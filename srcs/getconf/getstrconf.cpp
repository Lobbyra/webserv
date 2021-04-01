/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getstrconf.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:49:45 by mli               #+#    #+#             */
/*   Updated: 2021/04/01 12:27:51 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "getconf.hpp"

static const std::string whitespaces("\t\n\v\f\r ");

static void	add_content_to_str(std::string &res, const char *line) {
	while (*line) {
		if (!res.empty() && *(--res.end()) != ' ')
			res.push_back(' ');
		while (*line && whitespaces.find(*line) == std::string::npos) {
			if (*line == '#')
				return ;
			res.push_back(*line++);
		}
		while (*line && whitespaces.find(*line) != std::string::npos)
			++line;
	}
}

std::string	get_str_conf(const char *const path) {
	int			n;
	int			fd;
	char		*line;
	std::string	res;

	if ((fd = open(path, O_RDONLY)) < 0)
		throw std::logic_error("Cannot open config file");

	while ((n = get_next_line(fd, &line)) == 1) {
		add_content_to_str(res, line);
		free(line);
	}
	if (n == 0)
		free(line);
	else if (n == -1)
		throw std::logic_error("GNL");

	close(fd);
	return (res);
}

/*
int		main(int argc, char **argv)
{
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <nginx.conf>" << std::endl;
		return (1);
	}
	std::string conf = get_str_conf(argv[1]);

	std::cout << conf << std::endl;
	// check_curly_braces(conf);
	return (0);
}
*/
