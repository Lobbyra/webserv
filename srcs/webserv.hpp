#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <string>
# include <exception>
# include <fcntl.h>

# include "./lib/lib.hpp"
# include "./utils/utils.hpp"

struct  s_ipport {
    int             port;
    std::string     ip;
};

typedef std::string::iterator               t_strit;
typedef std::string::const_iterator         t_strcit;
typedef std::list<std::string>              t_strlst;
typedef std::map<int, std::string>          t_error_page;
typedef std::map<std::string, std::string>  t_cgi_param;

# include "c_location.hpp"
# include "c_server.hpp"
# include "./parse_conf/parse_conf.hpp"

std::list<c_server>     parse_conf(std::string path);

#endif // ****************************************************** MAIN_HPP end //
