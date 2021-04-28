#ifndef S_SOCKET_HPP
# define S_SOCKET_HPP

/* S_SOCKET
 * This structure is a multi-usage file descriptor tracker in our program.
 *
 * It's used for :
 *  - Save servers socket to listen.
 *  - Save client_fd received by accept() and linked to listen fd and server
 *    block from config file.
 *  - Set client_fd to physical files in file system to check if they are able
 *    to be read or to be written.
 *
 * This make this structure confused but our school subject restrict us to
 * call select() only in one place in our program.
 *
 * How to use as a :
 *  - Server :
 *      Use entry_socket and it will be good.
 *  - Client :
 *      Put entry_socket to 0 and use client_fd.
 *  - File :
 *      Use client_fd as fd you want to use select() and is_header* to true.
 */

#include <string>

#include <sys/socket.h> // For sockaddr type

#include "typedefs.hpp"
#include "s_ipport.hpp"
#include "c_server.hpp"

struct s_socket {
    int             client_fd;          // Client fd to comm. with it
    int             entry_socket;       // Socket where client landed
    bool            is_read_ready;      // Is data to read from client ?
    bool            is_write_ready;     // Is our client able to rec data ?
    bool            is_header_read;     // Is this client already parsed ?
    bool            is_header_received; // Is Entire request in RAM ?
    sockaddr      client_addr;        // Saving this variable for CGI
    s_ipport const  *ipport;            // Saving this variable for CGI
    c_server const  *server;            // Data from config linked to this req
};

std::ostream    &operator<<(std::ostream &o, s_socket const &i);

#endif
