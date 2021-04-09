# include "c_server.hpp"

/*
**    /// CONSTRUCTORS & DESTRUCTORS PART \\
*/
c_server::c_server(void) : client_max_body_size(0) {
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
    (void)src;
    return (*this);
}

std::ostream    &operator<<(std::ostream &o, c_server const &i) {
    (void)i;
    o /*<< DATA*/ << std::endl;
    return (o);
}
