#include "c_location.hpp"

/*
**    /// CONSTRUCTORS & DESTRUCTORS PART \\
*/
c_location::c_location(void) : client_max_body_size(0) {
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
    root = src.root;
    index = src.index;
    route = src.route;
    autoindex = src.autoindex;
    error_page = src.error_page;
    fastcgi_param = src.fastcgi_param;
    client_max_body_size = src.client_max_body_size;
    return (*this);
}

std::ostream    &operator<<(std::ostream &o, c_location const &i)
{
    o << \
    "location with route [" << i.route << "] :" << std::endl;

    if (i.root.empty() == false)
        o << "    root = [" << i.root << "]" << std::endl;
    if (i.index.empty() == false)
        o << "    index = [" << i.index << "]" << std::endl;
    if (i.autoindex.empty() == false)
        o << "    autoindex = [" << i.autoindex << "]" << std::endl;
    if (i.error_page.empty() == false)
        o << "    error_page = [" << i.error_page << "]" << std::endl;
    if (i.client_max_body_size > 0)
        o << "    client_max_body_size = [" << i.client_max_body_size << "]" << std::endl;
    return (o);
};
