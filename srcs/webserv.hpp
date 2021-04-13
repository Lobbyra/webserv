#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <string>
# include <exception>
# include <fcntl.h>

extern int indent_lvl;

# include "lib/lib.hpp"
# include "utils/utils.hpp"

struct  s_ipport {
    int             port;
    std::string     ip;
};

typedef std::string::iterator               t_strit;
typedef std::string::const_iterator         t_strcit;
typedef std::list<std::string>              t_strlst;
typedef std::list<int>                      t_fdlst;
typedef std::map<int, std::string>          t_error_page;
typedef std::map<std::string, std::string>  t_cgi_param;

# include "c_location.hpp"
# include "c_server.hpp"
# include "parse_conf/parse_conf.hpp"

struct s_client {
    int             client_fd;
    c_server const  *server;
};

std::list<c_server>     parse_conf(std::string path);
void                    webserv(std::list<c_server> const &conf);
t_fdlst                 init_listen(std::list<c_server> const &conf);

std::list<s_client>
ft_select(t_fdlst const &listen_ports, std::map<int, bool> *resp_avail);

#endif // ****************************************************** WEBSERV_HPP end //
