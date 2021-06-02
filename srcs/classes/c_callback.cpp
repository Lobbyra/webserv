#include "c_callback.hpp"
extern bool g_verbose;

c_callback::c_callback(void) {
    return ;
}

c_callback::c_callback(s_socket *client, s_request_header *request,
                       std::list<s_socket> *clients) {
    this->_fd_body = 0;
    this->_tmpfile = NULL;
    this->_bytes_write = 0;
    this->_bytes_read = 0;
    this->_host = false;
    this->_chunk_size = -1;
    this->clients = clients;
    this->_is_aborted = false;
    this->_out_tmpfile = NULL;
    this->_is_outfile_read = false;
    this->original_path = request->path;
    _init_s_socket(client);                 // Init client socket variables
    _init_request_header(request);          // Init request headers
    if (this->server) {                     // Init server variables
        _init_server_hpp(this->server);
        _server_init_route(this->server->location);
    }
    if (this->client_max_body_size != -1 &&
            this->content_length > (size_t)this->client_max_body_size) {
        this->status_code = 413;
    }
    if (this->fastcgi_pass != "" && _method_allow() == true) {  // CGI case
        _recipes = _init_recipe_cgi();
    } else {                                // Init recipes
        _init_meth_functions();
        _recipes = _meth_funs[this->method];
    }
    if (_recipes.empty() == true) {         // Case when methods is not known
        _recipes = _init_error_request();
    }
    _it_recipes = _recipes.begin();
    return ;
}

// c_callback::c_callback(c_callback const &src) {
//     *this = src;
// }

c_callback::~c_callback(void) {
    if (_tmpfile != NULL) {
        delete _tmpfile;
        _tmpfile = NULL;
    }
    if (_fd_body != 0)
        close(_fd_body);
    if (_out_tmpfile != NULL) {
        delete _out_tmpfile;
        _out_tmpfile = NULL;
    }
    if (this->status_code / 100 != 2) {
        remove_client(this->clients, this->client_fd, this->status_code);
    } else {
        reset_socket(this->client);
    }
    for (std::list<char*>::iterator it = _sending_buffer.begin();
            it != _sending_buffer.end(); ++it) {
        free(*it);
    }
    return ;
}

// c_callback	&c_callback::operator=(c_callback const &src) {
//     return (*this);
// }
//

/*
 * ####### PUBLIC FUNCTIONS
 */

void    c_callback::exec(void) {
    if (g_verbose)
        std::cout << "C_CALLBACK : exec()" << std::endl;
    std::list<s_socket>::iterator it = this->clients->begin();
    std::list<s_socket>::iterator ite = this->clients->end();

    while (it != ite) {
        if (&(*it) == this->client)
            break;
        ++it;
    }
    if (it == ite)
        _exit();
    if (this->is_over() == false) {
        if (this->status_code / 100 != 2 &&
                _recipes != _init_error_request()) {
            if (g_verbose)
                std::cout << "C_CALLBACK : turn recipe in error" << std::endl;
            _recipes = _init_error_request();
            _it_recipes = _recipes.begin();
        } else {
            if (g_verbose)
                std::cout << "C_CALLBACK : calling the task" << std::endl;
            (this->*(*_it_recipes))();
            if (_is_aborted == false && (this->status_code / 100 == 2 ||
                    _recipes == _init_error_request()))
                ++_it_recipes;
        }
    }
}

bool    c_callback::is_over(void) {
    return (_it_recipes == _recipes.end());
}

/* EXIT
 * This function is designed to be called inside a recipe to end and quit
 * callback before the end of all tasks.
 */
void    c_callback::_exit(void) {
    _it_recipes = _recipes.end();
    _is_aborted = true;
    return ;
}

/*
 * ####### PRIVATE FUNCTIONS
 */

/* _CONTINUE()
 * This function is created to be called at the end of a task to avoid
 * uselessly stop the request resolving and do all the tasks if possible.
 */
void    c_callback::_continue() {
    this->_it_recipes++;
    if (this->is_over() == false) {
        (this->*(*_it_recipes))();
    }
}

bool    c_callback::_method_allow(void) {
    t_strlst::iterator it, ite;
    bool               allow;

    it = this->methods.begin();
    ite = this->methods.end();
    allow = false;
    for (; it != ite; ++it)
        if (method == *it)
            allow = true;
    if (allow == false)
        this->status_code = 405;
    return (allow);
}

void    c_callback::_init_meth_functions(void) {
    if (this->host.empty() == true && this->status_code != 505) {
        this->status_code = 400;
        return ;
    }
    if (_method_allow() == false)
        return ;
    _meth_funs["PUT"] = _init_recipe_put();
    _meth_funs["GET"] = _init_recipe_get();
    _meth_funs["HEAD"] = _init_recipe_head();
    _meth_funs["POST"] = _init_recipe_post();
    _meth_funs["TRACE"] = _init_recipe_trace();
    _meth_funs["DELETE"] = _init_recipe_delete();
    _meth_funs["OPTIONS"] = _init_recipe_options();
}

void    c_callback::_init_request_header(s_request_header *request) {
    this->_resp_body = false;
    this->date = request->date;
    this->host = request->host;
    this->path = request->path;
    this->method = request->method;
    this->referer = request->referer;
    this->status_code = request->error;
    this->protocol = request->protocol;
    this->user_agent = request->user_agent;
    this->content_type = request->content_type;
    this->authorization = request->authorization;
    this->saved_headers = request->saved_headers;
    this->accept_charset = request->accept_charset;
    this->content_length = request->content_length;
    this->accept_language = request->accept_language;
    if (ft_strcmp(request->transfer_encoding.c_str(), "chunked") != 0 &&
        request->transfer_encoding.empty() == false)
        this->status_code = 400;
    else
        this->transfer_encoding = request->transfer_encoding;
    return ;
}

void        c_callback::_init_s_socket(s_socket *client) {
    this->client = client;
    this->content_length_h = 0;
    this->client_fd = client->client_fd;
    this->client_addr = client->client_addr;
    this->server = (c_server*)client->server;
    this->entry_socket = client->entry_socket;
    this->client_buffer = &(client->buffer);
    this->is_read_ready = &(client->is_read_ready);
    this->is_write_ready = &(client->is_write_ready);
    this->is_header_read = &(client->is_header_read);
}

void        c_callback::_init_server_hpp(c_server const *server) {
    this->root = server->root;
    this->index = server->index;
    this->srv_id = server->srv_id;
    this->listen = server->listen;
    this->location = server->location;
    this->autoindex = server->autoindex;
    this->error_page = server->error_page;
    this->server_name = server->server_name;
    this->fastcgi_param = server->fastcgi_param;
    this->client_max_body_size = server->client_max_body_size;
}

std::list<c_location>::iterator        c_callback::_server_find_route(
    std::list<c_location>::iterator &it, std::list<c_location>::iterator &ite) {
    std::list<c_location>::iterator     it_find;
    std::string                         tmp_path;
    size_t                              i = 0;
    int                                 status = 0;

    it_find = ite;
    i = this->path.find_first_of("/", 1);
    if (i != std::string::npos)
        tmp_path.insert(0, this->path, 0, i);
    else
        tmp_path = this->path;
    for (; it != ite; ++it)
    {
        if (ft_strncmp((*it).route.c_str(), ".", 1) == 0) { // location management by file
            std::string tmp_string;
            size_t found = this->path.find_last_of(".");
             if (found != std::string::npos) {
                tmp_string.insert(0, this->path, found, this->path.length());
                if ((ft_strncmp(tmp_string.c_str(), (*it).route.c_str(),
                        tmp_string.length())) == 0 &&
                        (tmp_string.length() == (*it).route.length())) {
                    it_find = it;
                    this->path.erase(0, i);
                    this->path.insert(0, this->root);
                    break ;
                }
            }
        }
        if (ft_strcmp((*it).route.c_str(), "/") == 0)
            it_find = it;
        if ((ft_strncmp(tmp_path.c_str(), (*it).route.c_str(),
                        tmp_path.length())) == 0 &&
                        (tmp_path.length() == (*it).route.length())) {
            it_find = it;
            status = 1;
        }
    }
    if (status == 1 && i != std::string::npos)
        this->path.erase(0, i);
    if (status == 1 && i == std::string::npos)
        this->path.clear();
    return (it_find);
}

void        c_callback::_server_init_route(std::list<c_location> location) {
    std::list<c_location>::iterator     it, ite;

    it = location.begin();
    ite = location.end();
    it = _server_find_route(it, ite);
    if (it != ite) {
        client_max_body_size = (*it).client_max_body_size;
        if ((*it).index.begin() != (*it).index.end())
            index = (*it).index;
        if ((*it).methods.empty() == false)
            methods = (*it).methods;
        if ((*it).root.empty() == false)
            root = (*it).root;
        if ((*it).autoindex.empty() == false)
            autoindex = (*it).autoindex;
        if ((*it).fastcgi_param.empty() == false)
            fastcgi_param = (*it).fastcgi_param;
        if ((*it).error_page.empty() == false)
            error_page = (*it).error_page;
        if ((*it).fastcgi_pass.empty() == false)
            fastcgi_pass = (*it).fastcgi_pass;
    }
}


std::ostream	&operator<<(std::ostream &o, c_callback const &src) {
    o << \
    COLOR_YELLOW_("Callback debug :") << std::endl << \
    COLOR_BLUE_("s_socket:") << std::endl << \
    COLOR_WHITE_("\tentry_socket: ") << src.entry_socket << \
    std::endl << \
    COLOR_WHITE_("\tclient_fd: ") << src.client_fd << \
    std::endl << \
    COLOR_BLUE_("s_request_header :") << std::endl << \
    COLOR_WHITE_("\tmethod: ") << src.method << \
    std::endl << \
    COLOR_WHITE_("\tpath: ") << src.path << \
    std::endl << \
    COLOR_WHITE_("\tprotocol: ") << src.protocol << \
    std::endl << \
    COLOR_WHITE_("\tdate: ") << src.date << \
    std::endl << \
    COLOR_WHITE_("\thost: ") << src.host << \
    std::endl << \
    COLOR_WHITE_("\treferer: ") << src.referer << \
    std::endl << \
    COLOR_WHITE_("\ttransfer_encoding: ") << src.transfer_encoding << \
    std::endl << \
    COLOR_WHITE_("\taccept_charset: ") << src.accept_charset << \
    std::endl << \
    COLOR_WHITE_("\taccept_language: ") << src.accept_language << \
    std::endl << \
    COLOR_WHITE_("\tauthorization: ") << src.authorization << \
    std::endl << \
    COLOR_WHITE_("\tcontent_type: ") << src.content_type << \
    std::endl << \
    COLOR_WHITE_("\tuser_agent: ") << src.user_agent << \
    std::endl << \
    COLOR_WHITE_("\tcontent_length: ") << src.content_length << \
    std::endl << \
    COLOR_WHITE_("\tstatus_code: ") << src.status_code << \
    std::endl;
    return o;
}
