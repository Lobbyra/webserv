#ifndef C_CALLBACK_HPP
# define C_CALLBACK_HPP

# include "../webserv.hpp"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>

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
    t_strlst                    methods;
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
    void    dumb_coucou(void) {
        std::string resp = "coucour\n";
        std::cout << resp << std::endl;
        send(client_fd, resp.c_str(), resp.size(), 0);
    };
    void    dumb_salut(void) {
        std::string resp = "salut\n";
        std::cout << resp << std::endl;
        send(client_fd, resp.c_str(), resp.size(), 0);
    };
    void    dumb_bonjour(void) {
        std::string resp = "bonjour\n";
        std::cout << resp << std::endl;
        send(client_fd, resp.c_str(), resp.size(), 0);
    };


private:
    /* ATTRIBUT INIT
     * Function used in construction to init attributs
     */
    void    _init_request_header(s_request_header request);
    void    _init_s_socket(s_socket client);
    void    _init_server_hpp(c_server const *server);
    void    _server_init_route(std::list<c_location> location);

    std::list<c_location>::iterator    _server_find_route(
    std::list<c_location>::iterator &it, std::list<c_location>::iterator &ite);


    /* _METH_FUNS
     * Contain relations between methods and recipes.
     */
    void                _init_meth_functions(void);
    std::map<std::string, std::list<t_task_f> > _meth_funs;

    std::string _response(void);

    /* _RECIPES
     * List of functions to resolve a request.
     */
    t_recipes                   _recipes;
    t_recipes_it                _it_recipes;

    /* _INIT_RECIPES_*
     * Get recipe for a specific methods.
     */
    std::list<t_task_f> _init_recipe_dumb(void);
    std::list<t_task_f> _init_recipe_head(void);
    std::list<t_task_f> _init_recipe_delete(void);
    std::list<t_task_f> _init_recipe_put(void);

    /* _FD_BODY
     * File descriptor that we will read and write in the client_fd.
     */
    int     _fd_body;

    /* _STATUS_MESSAGES
     * Contain relations between all status codes and messages.
     */
    std::map<int, std::string>  _status_message;
    void                        _init_map_status_message(void);
    std::string                 _get_status_line(int code);

    /* _RESP_HEADERS
     * Each node will be a line in headers that we will send in client_fd.
     * The first line is the status line.
     */
    std::list<std::string>  _resp_headers;

    std::string             _bad_request(void);
    void                    _send_bad_request(void);

    // HEAD RECIPE
    void    _meth_head_request_is_valid(void);
    void    _meth_head_response(void);
    void    _meth_head_send(void);

    // DELETE RECIPE
    int      _remove_directory(const char *path);
    void     _meth_delete_request_is_valid(void);
    void     _meth_delete_remove(void);
    void     _meth_delete_send(void);

    // GET RECIPE
    void    _meth_get_open(void);
    void    _meth_get_head(void);
    void    _meth_get_send(void);
    void    _meth_get_read(void);

    // PUT RECIPE
    void     _meth_put(void);
    void     _meth_put_send(void);

};

std::ostream	&operator<<(std::ostream &o, c_callback const &i);

#endif
