#ifndef MINI_SERV_HPP_
# define MINI_SERV_HPP_

# include <list>
# include <string>
# include <iostream>
# include <unistd.h>
# include "lib.h"

# define STDOUT 1

# define COLOR_RESET "\033[0m"
# define COLOR_BLUE "\033[1;34m"
# define COLOR_GREEN "\033[1;32m"

# define COLOR_BLUE_(str) COLOR_BLUE << str << COLOR_RESET
# define COLOR_GREEN_(str) COLOR_GREEN << str << COLOR_RESET

void        mini_serv(int port);
void		response(int client_fd);

#endif
