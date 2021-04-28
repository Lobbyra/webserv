#include <iostream>

#include "c_server.hpp"
#include "insert_stream_cont.hpp"

/*
**    /// CONSTRUCTORS & DESTRUCTORS PART \\
*/
c_server::c_server(void) : client_max_body_size(0), srv_id(0) {
    return ;
}

c_server::c_server(c_server const &src) {
    *this = src;
}

c_server::~c_server() {
    return ;
}

/*
**    /// FUNCTION MEMBER PART \\
*/

/*
**    /// OPERATOR OVERLOADS PART \\
*/
c_server   &c_server::operator=(c_server const &src) {
    this->client_max_body_size = src.client_max_body_size;
    this->srv_id = src.srv_id;
    this->index = src.index;
    this->listen = src.listen;
    this->server_name = src.server_name;
    this->root = src.root;
    this->autoindex = src.autoindex;
    this->fastcgi_param = src.fastcgi_param;
    this->error_page = src.error_page;
    this->location = src.location;
    return (*this);
}

std::ostream    &operator<<(std::ostream &o, c_server const &i) {
    o << "server [" << i.srv_id << "] :" << std::endl;
    if (i.listen.ip.empty() == false)
        o << "    listen = [" << i.listen << "]" << std::endl;
    if (i.server_name.empty() == false)
        o << "    server_name = [" << i.server_name << "]" << std::endl;
    if (i.root.empty() == false)
        o << "    root = [" << i.root << "]" << std::endl;
    if (i.index.empty() == false)
        o << "    index = [" << i.index << "]" << std::endl;
    if (i.autoindex.empty() == false)
        o << "    autoindex = [" << i.autoindex << "]" << std::endl;
    if (i.error_page.empty() == false)
        o << "    error_page = [\n" << i.error_page << "]" << std::endl;
    if (i.client_max_body_size > 0)
        o << "    client_max_body_size = [" << i.client_max_body_size << "]" << std::endl;
    if (i.fastcgi_param.empty() == false)
        o << "    fastcgi_param = [\n" << i.fastcgi_param << "]" << std::endl;
    if (i.location.empty() == false)
        o << "    " << i.location << std::endl;
    return (o);
};

std::ostream    &operator<<(std::ostream &o, s_ipport const &i)
{
    o << \
    "ip = " << i.ip << ", port = " << i.port;
    return (o);
};
