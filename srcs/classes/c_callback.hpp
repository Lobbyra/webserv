#ifndef C_CALLBACK_HPP
# define C_CALLBACK_HPP

# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netinet/ip.h>

# include <map>
# include <list>
# include <string>
# include <sstream>
# include <iostream>
# include <algorithm>

# include "lib.hpp"
# include "utils.hpp"
# include "colors.hpp"
# include "s_socket.hpp"
# include "s_ipport.hpp"
# include "c_server.hpp"
# include "c_tmpfile.hpp"
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

    c_callback(s_socket *client, s_request_header *request,
               std::list<s_socket> *clients);

    //s_socket
    int                         client_fd;
    int                         entry_socket;
    bool                        *is_read_ready;
    bool                        *is_write_ready;
    bool                        *is_header_read;
    c_server                    *server;
    s_socket                    *client;
    sockaddr                    client_addr;
    std::list<char*>            *client_buffer;
    std::list<s_socket>         *clients;

    // Variables from server block from config
    int                   client_max_body_size;
    int                   srv_id;
    t_strlst              index;
    t_strlst              methods;
    s_ipport              listen;
    t_strlst              server_name;
    std::string           root;
    std::string           autoindex;
    std::string           fastcgi_pass;
    t_cgi_param           fastcgi_param;
    t_error_page          error_page;
    std::list<c_location> location;

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
    std::list<std::string>      saved_headers;
    size_t                      content_length;
    size_t                      status_code;

    // Response variable that will dump in string to response
    size_t      content_length_h;
    std::string location_h;
    std::string last_modified_h;
    // [date] this header will be generated at response creation
    // [server] always be "drunserv"

    // Main Public functions
    bool                        is_over();
    void                        exec();

private:
    /* ATTRIBUT INIT
     * Function used in construction to init attributs
     */
    void    _init_request_header(s_request_header *request);
    void    _init_s_socket(s_socket *client);
    void    _init_server_hpp(c_server const *server);
    void    _server_init_route(std::list<c_location> location);

    void    _read_body(void);

    std::list<c_location>::iterator    _server_find_route(
                                         std::list<c_location>::iterator &it,
                                         std::list<c_location>::iterator &ite);


    /* _METH_FUNS
     * Contain relations between methods and recipes.
     */
    void                _init_meth_functions(void);
    std::map<std::string, std::list<t_task_f> > _meth_funs;
    bool                _method_allow(void);

    std::string _response(void);

    /* _INIT_RECIPES_*
     * Get recipe for a specific methods.
     */
    std::list<t_task_f> _init_recipe_get(void);
    std::list<t_task_f> _init_recipe_put(void);
    std::list<t_task_f> _init_recipe_cgi(void);
    std::list<t_task_f> _init_recipe_dumb(void);
    std::list<t_task_f> _init_recipe_head(void);
    std::list<t_task_f> _init_recipe_delete(void);
    std::list<t_task_f> _init_recipe_options(void);
    std::list<t_task_f> _init_recipe_post(void);
    std::list<t_task_f> _init_recipe_trace(void);
    std::list<t_task_f> _init_error_request(void);

    /* _RECIPES
     * List of functions to resolve a request.
     */
    t_recipes                   _recipes;
    t_recipes_it                _it_recipes;
    void _continue(void);
    void _exit(void);

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

    bool    _if_error_page_exist(void);
    void    _gen_resp_body(void);
    bool    _resp_body;

    /* TMPFILE
     * Temporary file class to save output of CGI or anything we want.
     * It's a pointer to not construct the class in case we do not need of temp
     * file.
     */
    c_tmpfile *_tmpfile;

    /* CHUNK TASK
     * Tasks to read chunk from client_fd.
     */
    int     _chunk_size;                // == -1 if im waiting a size, > 0 else
    void    _chunk_reading_size(void);  // Read the size of the chunk.
    void    _chunk_reading_chunk(void); // Read the chunk in stack and save it

    /* _FD_BODY
     * File descriptor that we will be read and write in the client_fd.
     */
    int     _fd_body;

    void    _fd_is_ready_to_send(void);
    void    _fd_is_ready_to_read(void);
    void    _send_respons_body(void);
    void    _send_respons(void);

    // GET RECIPE | HEAD RECIPE
    std::list<std::string> _dir_listening_page;
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
    void     _meth_put_open_fd(void);    // Create/open targeted ressource
    void     _meth_put_choose_in(void);  // Choose input fd (client_fd|chunk)
    void     _meth_put_write_body(void); // Loop to read/write from in/out fds
    int      _put_fd_in;                 // == tmpfile for chunk or client_fd
    int      _fd_to_write;               // == fd of targeted file
    int      _bytes_write;               // bytes already write in target file

    // POST RECIPE
    void    _create_tmp_file(void);
    void    _check_is_body_to_large(void);

    // OPTIONS RECIPE
    void    _gen_resp_header_options(void);

    // TRACE RECIPE
    void    _read_client_to_tmpfile(void);
    void    _write_request_line(void);

    // GGI RECIPE
    pid_t                  _pid; // pid of CGI child
    c_tmpfile              *_out_tmpfile;
    std::list<std::string> cgi_env_variables;

    void    _meth_cgi_init_meta(void); // Init specific var of CGI
    void    _meth_cgi_init_http(void); // Init additionnal headers from request
    void    _meth_cgi_save_client_in(void); // Store body in a file
    void    _meth_cgi_launch(void);    // Launch binary in child by fork()
    void    _meth_cgi_wait(void);      // Wait until child death for error 500
    void    _meth_cgi_send_http(void); // Get http data from cgi and send it
    void    _meth_cgi_send_resp(void); // Will translate and send the response

};

std::ostream	&operator<<(std::ostream &o, c_callback const &i);

#endif
