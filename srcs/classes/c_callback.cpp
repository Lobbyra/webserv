#include "c_callback.hpp"

c_callback::c_callback(void) {
    return ;
}

c_callback::c_callback(s_socket client, s_request_header request) {
    _init_s_socket(client);
    _init_request_header(request);
    if (this->server)
    {
        _init_server_hpp(this->server);
        _server_variable_check(this->server->location);
    }
    _init_map_status_message();
    _init_meth_functions();
    _recipes = _meth_funs[this->method];
    _it_recipes = _recipes.begin();
    return ;
}

// c_callback::c_callback(c_callback const &src) {
//     *this = src;
// }

c_callback::~c_callback(void) {
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
    if (this->is_over() == false) {
        (this->*(*_it_recipes))();
        _recipes.back();
        ++_it_recipes;
    }
}

bool    c_callback::is_over(void) {
    return (_it_recipes == _recipes.end());
}

/*
 * ####### PRIVATE FUNCTIONS
 */
void    c_callback::_init_map_status_message(void) {
    _status_message[200] = "OK";
    _status_message[201] = "Creapted";
    _status_message[203] = "Non-Authritative Information";
    _status_message[204] = "No Content";
    _status_message[205] = "Reset Content";
    _status_message[206] = "Partial Content";
    _status_message[400] = "Bad Request";
    _status_message[401] = "Unauthorized";
    _status_message[402] = "Payment Required";
    _status_message[403] = "Forbidden";
    _status_message[404] = "Not Found";
    _status_message[405] = "Method Not Allowed";
    _status_message[406] = "Not Acceptable";
    _status_message[408] = "Request Timeout";
    _status_message[409] = "Conflict";
    _status_message[410] = "Gone";
    _status_message[411] = "Length Required";
}

void    c_callback::_init_meth_functions(void) {
    _meth_funs["GET"] = _init_recipe_dumb();
}

std::list<c_callback::t_task_f>     c_callback::_init_recipe_dumb(void) {
    std::list<t_task_f> tasks; 

    tasks.push_back(&c_callback::dumb_coucou);
    tasks.push_back(&c_callback::dumb_salut);
    tasks.push_back(&c_callback::dumb_bonjour);

    return (tasks);
}

void    c_callback::_init_request_header(s_request_header request) {
    this->method = request.method;
    this->path = request.path;
    this->protocol = request.protocol;
    this->date = request.date;
    this->host = request.host;
    this->referer = request.referer;
    this->transfer_encoding = request.transfer_encoding;
    this->accept_charset = request.accept_charset;
    this->accept_language = request.accept_language;
    this->authorization = request.authorization;
    this->content_type = request.content_type;
    this->user_agent = request.user_agent;
    this->content_length = request.content_length;
    this->status_code = request.error;
    return ;
}

void        c_callback::_init_s_socket(s_socket client) {
    this->entry_socket = client.entry_socket;
    this->server = (c_server *)client.server;
    this->client_fd = client.client_fd;
    this->client_addr = client.client_addr;
}

void        c_callback::_init_server_hpp(c_server const *server) {
    this->client_max_body_size = server->client_max_body_size;
    this->srv_id = server->srv_id;
    this->index = server->index;
    this->listen = server->listen;
    this->server_name = server->server_name;
    this->root = server->root;
    this->autoindex = server->autoindex;
    this->fastcgi_param = server->fastcgi_param;
    this->error_page = server->error_page;
    this->location = server->location;
}

void        c_callback::_server_variable_check(std::list<c_location> location) {
    std::list<c_location>::iterator     it, ite;

    it = location.begin();
    ite = location.end();
    for (; it != ite; ++it)
    {
        if (this->path == (*it).route)
        {
            if((*it).client_max_body_size)
                this->server->client_max_body_size = (*it).client_max_body_size;
            if((*it).index.begin() != (*it).index.end())
                this->server->index = (*it).index;
            if ((*it).root.empty() == false)
                this->server->root = (*it).root;
            if ((*it).autoindex.empty() == false)
                this->server->autoindex = (*it).autoindex;
            if ((*it).fastcgi_param.empty() == false)
                this->server->fastcgi_param = (*it).fastcgi_param;
            if ((*it).error_page.empty() == false)
                this->server->error_page = (*it).error_page;
        }
    }
}


std::ostream	&operator<<(std::ostream &o, c_callback const &src) {
    o << COLOR_YELLOW << "Callback debug :" << COLOR_RESET << std::endl \
        << COLOR_BLUE << "s_socket:" << COLOR_RESET << std::endl \
        << COLOR_WHITE << "\tentry_socket: " << COLOR_RESET << src.entry_socket << "." << std::endl \
        // COLOR_WHITE << << "\tserver: << COLOR_RESET " << src.server << "." << std::endl 
        << COLOR_WHITE << "\tclient_fd: " << COLOR_RESET << src.client_fd << "." << std::endl \
        << COLOR_BLUE << "s_request_header:" << COLOR_RESET << std::endl \
        << COLOR_WHITE << "\tmethod: " << COLOR_RESET << src.method << "." << std::endl \
        << COLOR_WHITE << "\tpath: " << COLOR_RESET << src.path << "." << std::endl \
        << COLOR_WHITE << "\tprotocol: " << COLOR_RESET << src.protocol << "." << std::endl \
        << COLOR_WHITE << "\tdate: " << COLOR_RESET << src.date << "." << std::endl \
        << COLOR_WHITE << "\thost: " << COLOR_RESET << src.host << "." << std::endl \
        << COLOR_WHITE << "\treferer: " << COLOR_RESET << src.referer << "." << std::endl \
        << COLOR_WHITE << "\ttransfer_encoding: " << COLOR_RESET << src.transfer_encoding << "." << std::endl \
        << COLOR_WHITE << "\taccept_charset: " << COLOR_RESET << src.accept_charset << "." << std::endl \
        << COLOR_WHITE << "\taccept_language: " << COLOR_RESET << src.accept_language << "." << std::endl \
        << COLOR_WHITE << "\tauthorization: " << COLOR_RESET << src.authorization << "." << std::endl \
        << COLOR_WHITE << "\tcontent_type: " << COLOR_RESET << src.content_type << "." << std::endl \
        << COLOR_WHITE << "\tuser_agent: " << COLOR_RESET << src.user_agent << "." << std::endl \
        << COLOR_WHITE << "\tcontent_length: " << COLOR_RESET << src.content_length << "." << std::endl \
        << COLOR_WHITE << "\terror: " << COLOR_RESET << src.status_code << "." << std::endl;
    return o;
}
