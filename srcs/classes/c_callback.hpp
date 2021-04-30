#ifndef C_CALLBACK_HPP
# define C_CALLBACK_HPP

# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/socket.h>

# include <map>
# include <list>
# include <string>
# include <iostream>
# include <sstream>

# include "lib.hpp"
# include "utils.hpp"
# include "colors.hpp"
# include "s_socket.hpp"
# include "s_ipport.hpp"
# include "c_server.hpp"
# include "c_location.hpp"
# include "our_typedefs.hpp"
# include "std_typedefs.hpp"
# include "s_request_header.hpp"
# include "../lib/GNL/get_next_line.h"

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

    c_callback(s_socket client, s_request_header request,
               std::list<s_socket> *clients);

    //s_socket
    std::list<s_socket>         *clients;
    int                         entry_socket;
    c_server                    *server;
    int                         client_fd;
    sockaddr                    client_addr;
    bool                        *is_read_ready;
    bool                        *is_write_ready;
    bool                        *is_header_read;

    // Variables from server block from config
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

    // Variables from client request
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

    // Response variable that will dump in string to response
    int         content_length_h;
    std::string location_h;
    std::string last_modified_h;
    // [date] this header will be generated at response creation
    // [server] always be "drunserv"

    // Main Public functions
    bool                        is_over();
    void                        exec();

    // dumb Functions
    void    dumb_coucou(void) {
        std::string resp = "coucour\n";
        std::cout << resp << std::endl;
        //send(client_fd, "", 1, 0); // shit to remove but make curl working idkw
    };
    void    dumb_salut(void) {
        std::string resp = "salut\n";
        std::cout << resp << std::endl;
    };
    void    dumb_bonjour(void) {
        std::string resp = "bonjour\n";
        std::cout << resp << std::endl;

        std::list<std::string> _headers;
        this->status_code = 200;
        this->content_length_h = 0;
        this->location_h = "/parla/sijissuis/";
        this->last_modified_h = "hier";
        _gen_resp_headers();
        send(client_fd, _resp_headers.c_str(), _resp_headers.size(), 0);
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

    /* _INIT_RECIPES_*
     * Get recipe for a specific methods.
     */
    std::list<t_task_f> _init_recipe_dumb(void);
    std::list<t_task_f> _init_recipe_get(void);
    std::list<t_task_f> _init_recipe_head(void);
    std::list<t_task_f> _init_recipe_delete(void);
    std::list<t_task_f> _init_recipe_put(void);
    std::list<t_task_f> _init_recipe_options(void);
    std::list<t_task_f> _init_error_request(void);

    /* _RECIPES
     * List of functions to resolve a request.
     */
    t_recipes                   _recipes;
    t_recipes_it                _it_recipes;

    /* _STATUS_MESSAGES
     * Contain relations between all status codes and messages.
     */
    std::string                 _get_status_line(int code);


    /* _GEN_RESP_HEADERS
     * Generate headers in string form including status line in _headers
     */
    void  _gen_error_header_and_body(void);
    void  _gen_resp_headers(void);
    std::string _resp_headers;

    void    _gen_resp_body(void);
    std::string _resp_body;

    /* _FD_BOD
     * File descriptor that we will be read and write in the client_fd.
     */
    int     _fd_body;

    void    _fd_is_ready_to_send(void);
    void    _send_respons(void);

    // GET RECIPE | HEAD RECIPE
    void            _meth_get_request_is_valid(void);
    std::string     _find_index_if_exist(void);

    // DELETE RECIPE
    int      _remove_directory(const char *path);
    void     _meth_delete_request_is_valid(void);
    void     _meth_delete_remove(void);

    // GET RECIPE
    void    _meth_get_open(void);
    void    _meth_get_head(void);
    void    _meth_get_send(void);
    void    _meth_get_read(void);

    // PUT RECIPE
    void     _meth_put_open_fd(void);
    void     _meth_put_fd_is_ready_to_write(void);
    void     _meth_put_write_body(void);
    s_socket _fd_to_write;

    // OPTIONS RECIPE
    void    _gen_resp_header_options(void);

};

std::ostream	&operator<<(std::ostream &o, c_callback const &i);

#endif
