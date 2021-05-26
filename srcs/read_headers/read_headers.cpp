#include <map>
#include <list>
#include <string>

#include "lib.hpp"
#include "s_socket.hpp"
#include "read_headers.hpp"

extern bool g_verbose;

/* REMOVE_CLIENT
 * This function will remove the client gived from the list of client cause of
 * EOF/connection closed or recv return an error.
 */
static void remove_client(std::list<s_socket> *clients,
        std::list<s_socket>::iterator client, ssize_t bytes_read) {
    std::string closing_cause = "";
    std::list<char*>::iterator it_buf = client->buf_header.begin();
    std::list<char*>::iterator ite_buf = client->buf_header.end();

    if (g_verbose == true) {
        if (bytes_read == -1) {
            closing_cause = "read error.";
        } else if (bytes_read == 0) {
            closing_cause = "client closed the connection.";
        }
        std::cout <<                                                       \
            "[" << client->client_fd << "] Connection closed due to : " << \
            closing_cause <<                                               \
        std::endl;
    }
    while (it_buf != ite_buf) {
        free(*it_buf);
        client->buf_header.erase(it_buf++);
    }
    close(client->client_fd);
    clients->erase(client);
    return ;
}

#define BUFF_SIZE_SOCKET 1024

/* READ_SOCKET
 * This function will read socket and save data read in the buffer header.
 * Return what recv return.
 */
static ssize_t     read_socket(std::list<char*> *buf_header, int client_fd) {
    char    *read_buffer = NULL;
    ssize_t bytes_read = 0;

    if (!(read_buffer = (char*)malloc(sizeof(char) * (BUFF_SIZE_SOCKET + 1))))
        return (NULL);
    ft_bzero(read_buffer, BUFF_SIZE_SOCKET + 1);
    bytes_read = recv(client_fd, read_buffer, BUFF_SIZE_SOCKET, 0);
    if (bytes_read > 0)
        buf_header->push_back(read_buffer);
    return (bytes_read);
}

/* PARSE_BUFFER
 * This function will parse the buffer and put data parsed in the header
 * given.
 */
static void parse_buffer(std::list<char*> *buffer, s_request_header *headers,
                    std::map<std::string, f_request_header> *headers_parsers,
                    bool *is_status_line_read) {
    std::string                  header_to_parse;
    std::map<std::string, void*> headers_ptrs;

    header_to_parse = get_header(buffer, *is_status_line_read);
    if (header_to_parse != "")
        headers_ptrs = init_header_ptrs(headers);
    while (header_to_parse != "" && headers->error / 100 == 2) {
        if (*is_status_line_read == false) {            // Status line parsing
            parse_status_line(header_to_parse, &headers_ptrs);
            *is_status_line_read = true;
        } else {                                        // Common head parsing
            if (parse_header(header_to_parse, &headers_ptrs, headers_parsers)
                    == 1) {                             // Double host error
                headers->error = 400;
            }
            headers->saved_headers.push_back(header_to_parse);
        }
        header_to_parse = get_header(buffer, is_status_line_read);
    }
    return ;
}

/* READ_HEADERS
 * This function will read what is possible to read from clients after
 * select() calling from webserv.cpp. It will parse header and status line when
 * one is recieved from socket. It return true if almost one complete header
 * part from a client is recieved.
 */
bool    read_headers(std::list<s_socket> *clients) {
    bool        is_one_req_ready = false;
    ssize_t     bytes_read = 0;
    std::list<s_socket>::iterator           it = clients->begin();
    std::list<s_socket>::iterator           ite = clients->end();
    std::map<std::string, f_request_header> headers_parsers;

    headers_parsers = init_header_parsers();
    while (it != ite) {
        // NON AVALAIBLE CLIENTS SKIPPING
        if (it->is_read_ready == false || it->client_fd == 0 ||
                it->is_header_read == true) {
            ++it;
            continue;
        }
        // READ DATA FROM CLIENT
        bytes_read = read_socket(&it->buf_header, it->client_fd);
        if (bytes_read == 0 || bytes_read == -1) { // End of connection
            remove_client(clients, it++, bytes_read);
            continue;
        }
        // SAVE IF THERE A CRLF HEAD_BODY SEPARATOR READ IN BUFFER
        it->is_header_read = is_sep_header(&it->buf_header,
                                           it->is_status_line_read);
        is_one_req_ready |= it->is_header_read;    // At least one req read ret
        // PARSING DATA RECIEVED
        parse_buffer(&(it->buf_header), &(it->headers), &headers_parsers,
                     &(it->is_status_line_read));
        if (it->is_header_read == true) {
            cut_buffer(&(it->buf_header), 2);
        }
        if (it->headers.error / 100 != 2)          // Read finished if error
            it->is_header_read = true;

        ++it;
    }
    return (is_one_req_ready);
}
