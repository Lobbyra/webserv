#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <string>
# include <exception>
# include <fcntl.h>
# include <netinet/in.h> // struct sockaddr_in

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

typedef struct sockaddr t_sockaddr;
typedef struct sockaddr_in t_sockaddr_in;
typedef std::map<int, bool> t_respmap;

struct s_socket {
    int             entry_socket;
    c_server const  *server;
    int             client_fd;
    t_sockaddr      client_addr;
};

typedef std::list<s_socket>     t_socketlst;

std::list<c_server>     parse_conf(std::string path);
void                    webserv(std::list<c_server> const &conf);
t_socketlst             init_listen(std::list<c_server> const &conf);

t_socketlst ft_select(t_socketlst const &listen_ports, t_respmap *resp_avail);

#endif // *************************************************** WEBSERV_HPP end //
