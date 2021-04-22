#ifndef C_CALLBACK_HPP
# define C_CALLBACK_HPP

#include "../webserv.hpp"

struct s_request_header;

class	c_callback
{
public:
    typedef void (c_callback::*t_task_f)(void);
    typedef std::list<t_task_f>                 t_recipes;
    typedef std::list<t_task_f>::const_iterator t_recipes_it;

    c_callback(void);
    // c_callback(c_callback const &src);
    // c_callback &operator=(c_callback const &src);
    virtual ~c_callback();

    c_callback(s_socket client, s_request_header request);

    //s_socket
    int                         entry_socket;
    c_server                    *server;
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
    size_t                      status_code;

    // Main functions
    bool                        is_over();
    void                        exec();

    // dumb Functions
    void    dumb_coucou(void) { std::cout << "coucou" << std::endl; };
    void    dumb_salut(void) { std::cout << "salut" << std::endl; };
    void    dumb_bonjour(void) { std::cout << "bonjour" << std::endl; };


private:

    void    _init_request_header(s_request_header request);
    void    _init_s_socket(s_socket client);
    void    _init_server_hpp(c_server const *server);
    void    _server_variable_check(std::list<c_location> location);
    void    _init_map_status_message(void);

    t_recipes                   _recipes;
    t_recipes_it                _it_recipes;
    std::map<std::string, std::list<t_task_f> > _meth_funs;
    std::map<int, std::string>                  _status_message;

    void                _init_meth_functions(void);
    std::list<t_task_f> _init_recipe_dumb(void);
    std::list<t_task_f> _init_recipe_head(void);
    std::list<t_task_f> _init_recipe_delete(void);

    /*******************************************
	*****              Method              *****
	*******************************************/
    // general
    std::string     _response(void);

    // head
    void     _head_request_is_valid(void);
    void     _head_response(void);

    // delete
    void     _delete_request_is_valid(void);

};

std::ostream	&operator<<(std::ostream &o, c_callback const &i);

#endif
