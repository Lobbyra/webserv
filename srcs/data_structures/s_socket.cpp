#include "s_socket.hpp"
#include "colors.hpp"

std::ostream    &operator<<(std::ostream &o, s_socket const &i) {
    o << "{";

    o << COLOR_WHITE_("entry_socket") << " = " << i.entry_socket;
    o << COLOR_WHITE_(", client_fd") << " = " << i.client_fd;
    o << COLOR_WHITE_(", is_read_ready") << " = " << \
        (i.is_read_ready ? COLOR_GREEN : COLOR_RED) << \
        std::boolalpha << i.is_read_ready << COLOR_RESET;
    o << COLOR_WHITE_(", is_write_ready") << " = " << \
        (i.is_write_ready ? COLOR_GREEN : COLOR_RED) << \
        std::boolalpha << i.is_write_ready << COLOR_RESET;
    o << COLOR_WHITE_(", is_header_read") << " = " << \
        (i.is_header_read ? COLOR_GREEN : COLOR_RED) << \
        std::boolalpha << i.is_header_read << COLOR_RESET;

    o << "}" << std::endl;
    return (o);
}
