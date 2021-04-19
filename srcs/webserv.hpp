#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <queue>
# include <string>
# include <iostream>
# include <exception>
# include <fcntl.h>
# include <netinet/in.h> // struct sockaddr_in

extern int indent_lvl;

# include "lib/lib.hpp"
# include "utils/utils.hpp"

#define COLOR_RESET			"\033[0m"
#define COLOR_RED			"\033[1;31m"
#define COLOR_BLUE			"\033[1;34m"
#define COLOR_GREEN			"\033[1;32m"
#define COLOR_WHITE			"\033[1;37m"
#define COLOR_YELLOW		"\033[33m"
#define COLOR_CYAN			"\033[1;36m"

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

struct s_request_header {
        std::string                 method;
        std::string                 path;
        std::string                 protocol;
        std::string                 date;
        std::string                 host;
        std::string                 referer;
        std::string                 transfer_encoding;
        std::list<std::string>      accept_charset;
        std::list<std::string>      accept_language;
        std::list<std::string>      authorization;
        std::list<std::string>      content_type;
        std::list<std::string>      user_agent;
        size_t                      content_length;
        size_t                      error;
};

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

# include "parse_request_header/parse_request.hpp"

void            init_callback(t_socketlst clients,
                              std::list<s_request_header> requests);

#endif // *************************************************** WEBSERV_HPP end //
