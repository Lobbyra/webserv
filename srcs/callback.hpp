#ifndef CALLBACK_HPP
# define CALLBACK_HPP

#include "webserv.hpp"

struct s_request_header;

class	c_callback
{
public:

    c_callback(void);
    // c_callback(c_callback const &src);
    // c_callback &operator=(c_callback const &src);
    virtual ~c_callback();

    c_callback(s_socket client, s_request_header request);

    //s_socket
    int                         entry_socket;
    c_server const              *server;
    int                         client_fd;
    t_sockaddr                  client_addr;

    //c_server_hpp
    int                         client_max_body_size;
    int                         srv_id;
    t_strlst                    index;
    s_ipport                    listen;
    t_strlst                    server_name;
    std::string                 root;
    std::string                 autoindex;
    t_cgi_param                 fastcgi_param;
    t_error_page                error_page;
    std::list<c_location>       location;

    //s_request_header
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

    //other
    /*
    std::map<int, bool>         *resp_avail;
    t_recipes                   recipe;
    t_recipes_it                it_recipes;
    bool                        is_over() {};
    void                        exec() {};*/

private:

    void    _init_request_header(s_request_header request);
    void    _init_s_socket(s_socket client);
    void    _init_server_hpp(c_server const *server);
    void    _server_variable_check(c_location location);

};

// std::ostream	&operator<<(std::ostream &o, c_callback const &i);

#endif