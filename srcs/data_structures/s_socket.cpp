#include "s_socket.hpp"
#include "colors.hpp"
#include <stdlib.h>

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
    std::endl;
    o <<                                                         \
    COLOR_WHITE_(" is_status_line_read") << " = " <<             \
        std::boolalpha << COLOR_BOOL_(i.is_status_line_read) <<  \
    COLOR_WHITE_(", is_callback_created") << " = " <<            \
        std::boolalpha << COLOR_BOOL_(i.is_callback_created) <<  \
    COLOR_WHITE_(", is_cache_resp") << " = " <<            \
        std::boolalpha << COLOR_BOOL_(i.is_cache_resp) <<  \
    std::endl;
  //  o << COLOR_WHITE_(" buffer") << " = " << i.buffer;
//    o << COLOR_WHITE_(" len_buf_parts") << " = " << i.len_buf_parts;

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

/* RESET_SOCKET
 * This function reset to default values the socket given. It does not affect
 * connection values to not break a keep-alive connection.
 */
void    reset_socket(s_socket *s) {
    std::list<char*>::iterator it_buf = s->buffer.begin();
    std::list<char*>::iterator ite_buf = s->buffer.end();

    s->server = NULL;
    s->is_read_ready = false;
    s->is_cache_resp = false;
    s->is_write_ready = false;
    s->is_header_read = false;
    reset_header(&(s->headers));
    s->is_status_line_read = false;
    s->is_callback_created = false;
    s->len_buf_parts.clear();
    while (it_buf != ite_buf) { // Clean header buffer
        free(*it_buf);
        s->buffer.erase(it_buf++);
    }
}

void    reset_similar(s_similar_get_req *simi) {
    simi->host = "";
    simi->ipport = NULL;
    simi->respons = "";
    simi->path_respons = "";
}
