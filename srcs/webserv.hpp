#ifndef WEBSERV_HPP
# define WEBSERV_HPP

// C++ HEADERS
# include <queue>
# include <string>
# include <iostream>
# include <exception>
# include <algorithm>

// C HEADERS
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <netinet/in.h> // struct sockaddr_in

# define SERVER_NAME "drunkserv 0.1"
# define HTTP_DATE_FORMAT "%a, %d %b %Y %H:%M:%S %Z"

extern int indent_lvl;

# include "lib/lib.hpp"
# include "utils/utils.hpp"

# define COLOR_RESET    "\033[0m"
# define COLOR_RED      "\033[1;31m"
# define COLOR_BLUE     "\033[1;34m"
# define COLOR_CYAN     "\033[1;36m"
# define COLOR_GREEN    "\033[1;32m"
# define COLOR_WHITE    "\033[1;37m"
# define COLOR_YELLOW   "\033[33m"

# define COLOR_RED_(str) COLOR_RED << str << COLOR_RESET
# define COLOR_BLUE_(str) COLOR_BLUE << str << COLOR_RESET
# define COLOR_CYAN_(str) COLOR_CYAN << str << COLOR_RESET
# define COLOR_GREEN_(str) COLOR_GREEN << str << COLOR_RESET
# define COLOR_WHITE_(str) COLOR_WHITE << str << COLOR_RESET
# define COLOR_YELLOW_(str) COLOR_YELLOW << str << COLOR_RESET

struct  s_ipport {
    int             port;
    std::string     ip;
};

bool    operator==(s_ipport const &a, s_ipport const &b);
bool    operator!=(s_ipport const &a, s_ipport const &b);

typedef std::string::iterator               t_strit;
typedef std::string::const_iterator         t_strcit;
typedef std::list<std::string>              t_strlst;
typedef std::list<int>                      t_fdlst;
typedef std::map<int, std::string>          t_error_page;
typedef std::map<std::string, std::string>  t_cgi_param;

# include "classes/c_location.hpp"
# include "classes/c_server.hpp"
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
    s_ipport const  *ipport;
    c_server const  *server;
    int             client_fd;
    t_sockaddr      client_addr;
    bool            is_read_ready;
    bool            is_write_ready;
    bool            is_header_read;
};

std::ostream    &operator<<(std::ostream &o, s_socket const &i);

typedef std::list<s_socket>     t_socketlst;

std::list<c_server>     parse_conf(std::string path);
void                    webserv(std::list<c_server> const &conf);
t_socketlst             init_clients(std::list<c_server> const &conf);
void                    ft_select(t_socketlst *const clients);

void    assign_server_to_clients(std::list<c_server> const &conf, \
    t_socketlst *const clients, std::list<s_request_header> const &reqs);

# include "parse_request_header/parse_request.hpp"

void            init_callback(t_socketlst clients,
                              std::list<s_request_header> requests);

# include "classes/c_callback.hpp"
# include "classes/c_task_queue.hpp"

#endif // *************************************************** WEBSERV_HPP end //
