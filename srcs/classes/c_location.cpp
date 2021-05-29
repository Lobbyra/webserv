#include "c_location.hpp"

int indent_lvl = 1;

/*
**    /// CONSTRUCTORS & DESTRUCTORS PART \\
*/
c_location::c_location(void) : client_max_body_size(-1) {
    return ;
}

c_location::c_location(c_location const &src) {
    *this = src;
}

c_location::~c_location() {
    return ;
}

/*
**    /// FUNCTION MEMBER PART \\
*/

/*
**    /// OPERATOR OVERLOADS PART \\
*/
c_location   &c_location::operator=(c_location const &src) {
    this->root = src.root;
    this->index = src.index;
    this->route = src.route;
    this->methods = src.methods;
    this->autoindex = src.autoindex;
    this->error_page = src.error_page;
    this->fastcgi_pass = src.fastcgi_pass;
    this->fastcgi_param = src.fastcgi_param;
    this->client_max_body_size = src.client_max_body_size;
    return (*this);
}

std::ostream    &operator<<(std::ostream &o, c_location const &i) {
    indent_lvl++;
    o << \
    "location with route [" << i.route << "] :" << std::endl;

    if (i.root.empty() == false)
        o << "    root = [" << i.root << "]" << std::endl;
    if (i.index.empty() == false)
        o << "    index = [" << i.index << "]" << std::endl;
    if (i.methods.empty() == false)
        o << "    methods = [" << i.methods << "]" << std::endl;
    if (i.autoindex.empty() == false)
        o << "    autoindex = [" << i.autoindex << "]" << std::endl;
    if (i.error_page.empty() == false)
        o << "    error_page = [\n" << i.error_page << "]" << std::endl;
    if (i.client_max_body_size >= 0) {
        o << \
        "    client_max_body_size = [" << i.client_max_body_size << "]" << \
        std::endl;
    }
    if (i.fastcgi_param.empty() == false)
        o << "    fastcgi_param = [\n" << i.fastcgi_param << "]" << std::endl;
    if (i.fastcgi_pass.empty() == false)
        o << "    fastcgi_pass = [" << i.fastcgi_pass << "]" << std::endl;
    indent_lvl--;
    return (o);
};
