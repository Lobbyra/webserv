#include "callback.hpp"

c_callback::c_callback(void) {
    return ;
}

c_callback::c_callback(s_socket client, s_request_header request) {
    _init_s_socket(client);
    _init_request_header(request);
    if (this->server)
        _init_server_hpp(this->server);
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

void        c_callback::_init_request_header(s_request_header request) {
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
    this->error = request.error;
    return ;
}

void        c_callback::_init_s_socket(s_socket client) {
    this->entry_socket = client.entry_socket;
    this->server = client.server;
    this->client_fd = client.client_fd;
    this->client_addr = client.client_addr;
}

void        c_callback::_init_server_hpp(c_server *server) {
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

// void        c_callback::_server_variable_check(c_location location) {

// }


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
    << COLOR_WHITE << "\terror: " << COLOR_RESET << src.error << "." << std::endl;
    return o;
}

void            init_callback(t_socketlst clients, std::list<s_request_header> requests)
{

    c_callback      callback(clients.front(), requests.front());
    std::cout << callback << std::endl;
}