#include "s_socket.hpp"
#include "colors.hpp"

std::ostream    &operator<<(std::ostream &o, s_socket const &i) {
    o << "{";

    o << COLOR_WHITE_("entry_socket") << " = " << i.entry_socket;
    o << COLOR_WHITE_(", client_fd") << " = " << i.client_fd;
    o << COLOR_WHITE_(", is_read_ready") << " = " << \
        std::boolalpha << COLOR_BOOL_(i.is_read_ready);
    o << COLOR_WHITE_(", is_write_ready") << " = " << \
        std::boolalpha << COLOR_BOOL_(i.is_write_ready);
    o << COLOR_WHITE_(", is_header_read") << " = " << \
        std::boolalpha << COLOR_BOOL_(i.is_header_read);

    o << "}" << std::endl;
    return (o);
}

std::ostream    &operator<<(std::ostream& os, const std::list<s_socket>& v)
{
    std::list<s_socket>::const_iterator it;

    os << COLOR_YELLOW_("Clients:") << std::endl;
    for (it = v.begin(); it != v.end(); ++it)
        os << *it;
    return os;
}
