#include "s_socket.hpp"
#include "colors.hpp"

std::ostream    &operator<<(std::ostream &o, s_socket const &i) {
    o << "{" <<                                                       \
    COLOR_WHITE_("entry_socket") << " = " << i.entry_socket <<        \
    COLOR_WHITE_(", client_fd") << " = " << i.client_fd << std::endl;
    o <<                                                   \
    COLOR_WHITE_(" is_read_ready") << " = " <<             \
        std::boolalpha << COLOR_BOOL_(i.is_read_ready) <<  \
    COLOR_WHITE_(", is_write_ready") << " = " <<           \
        std::boolalpha << COLOR_BOOL_(i.is_write_ready) << \
    COLOR_WHITE_(", is_header_read") << " = " <<           \
        std::boolalpha << COLOR_BOOL_(i.is_header_read) << \
    "}" << std::endl;
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
