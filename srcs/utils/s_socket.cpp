#include "s_socket.hpp"

std::ostream    &operator<<(std::ostream &o, s_socket const &i) {
    o <<                                                                      \
    "entry_socket = " << i.entry_socket << std::endl <<                       \
    "client_fd = " << i.client_fd << std::endl <<                             \
    "is_read_ready = " << std::boolalpha << i.is_read_ready << std::endl <<   \
    "is_write_ready = " << std::boolalpha << i.is_write_ready << std::endl << \
    "is_header_read = " << std::boolalpha << i.is_header_read << std::endl << \
    std::endl;

    return (o);
}
