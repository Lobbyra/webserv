#include "c_callback.hpp"
#include <sys/time.h>
extern bool g_verbose;

/* C_CALLBACK_UTILS_CPP
 * This file contain all utils member functions used to create and
 * response to a request.
 * This file MUST contain only member functions to all method recipes.
 */

/* GEN_RESP_HEADERS()
 * This function will return a list of string ready to be tranformed in text of
 * headers that we will have to send to client.
 *
 * This function add the status line.
 */
static std::string get_content_length(int content_length) {
    char *str_content_length;
    std::string str_cl;

    str_content_length = ft_itoa(content_length);
    if (str_content_length == NULL)
        throw std::logic_error("gen_resp_headers : memory allocation failed");
    str_cl = str_content_length;
    free(str_content_length);
    return (str_cl);
}

# define HTTP_DATE_FORMAT "%a, %d %b %Y %H:%M:%S %Z"

static std::string get_date(void) {
    struct timeval  curr_time;
    char            result[100];

    errno = 0;
    bzero(result, 100);
    if (gettimeofday(&curr_time, NULL) == -1) {
        throw std::logic_error("get_time_of_day() failed");
    }
    strftime(result, 100, HTTP_DATE_FORMAT, localtime(&(curr_time.tv_sec)));
    if (errno != 0) {
        throw std::logic_error("strftime() failed");
    }
    return (result);
}

static void grh_add_headers(std::list<std::string> &headers, c_callback &cb) {
    // SERVER
    headers.push_back("Server: Drunkserv v6.66");
    // DATE
    try {
        headers.push_back("Date: " + get_date());
    } catch (std::exception &e) {
        cb.status_code = 500;
        std::cerr << e.what() << std::endl;
    }
    // CONTENT-LENGTH
    try {
        headers.push_back("Content-Length: " + \
                          get_content_length(cb.content_length_h));
    } catch (std::exception &e) {
        cb.status_code = 500;
        std::cerr << e.what() << std::endl;
    }
    // LOCATION
    if (cb.location_h != "")
        headers.push_back("Location: " + cb.location_h);
    // LEST_MODIFIED
    if (cb.last_modified_h != "")
        headers.push_back("Last-Modified: " + cb.last_modified_h);
}

void    c_callback::_read_body(void) {
    int                             status;
    char                            buf[1024];
    std::list<s_socket>::iterator   it, ite;

    if (this->method == "PUT")
        return ;
    if (g_verbose)
        std::cout << "TASK : _read_body()" << std::endl;
    errno = 0;
    if (*this->is_read_ready == false) {
        return ;
    }
    else {
        ft_bzero(buf, 1024);
        status = read(client_fd, buf, 1023);
        if (status > 0)
            --_it_recipes;
        else if (status == -1) {
            status_code = 500;
            --_it_recipes;
            std::cerr << "error: _read_body() " << strerror(errno) << std::endl;
        }
    }
}

void    c_callback::_gen_resp_headers(void) {
    if (g_verbose)
        std::cout << "TASK : _gen_resp_headers()" << std::endl;
    std::list<std::string> headers;

    headers.push_back(get_status_line(status_code));
    grh_add_headers(headers, *this);
    headers.push_back("\r\n");
    if (_dir_listening_page.size() > 0) {
        headers.insert(headers.end(), _dir_listening_page.begin(),
                                      _dir_listening_page.end());
    }
    _resp_headers = lststr_to_strcont(headers, "\r\n");
}

/* FD_IS_READY_TO_READ()
 * Function which verifies that we can read in the fd
 * If not decrement the iterator it_recipes
 */
void                    c_callback::_fd_is_ready_to_read(void) {
    if (g_verbose)
        std::cout << "TASK : _fd_is_ready_to_read()" << std::endl;
    if (*(this->is_read_ready) == false) {
        _it_recipes--;
    }
}

/* FD_IS_READY_TO_SEND()
 * Function which verifies that we can write in the fd
 * If not decrement the iterator it_recipes
 */
void                    c_callback::_fd_is_ready_to_send(void) {
    if (g_verbose)
        std::cout << "TASK : _fd_is_ready_to_send()" << std::endl;
    if (*(this->is_write_ready) == false) {
        _it_recipes--;
    }
}

#define BUFFER_READ 4096

/* SEND_RESPONS_BODY()
 * Send the respons body from the server to the client
 * Open the requested file, read the file, and send line by line
 */
void                    c_callback::_send_respons_body(void) {
    char            buf[BUFFER_READ];
    int             bytes_read;
    if (g_verbose)
        std::cout << "TASK : _send_respons_body()" << std::endl;

    if (_resp_body != true) {
        return ;
    }
    if (_fd_body == 0) {                      // Open requested file
        _fd_body = open(this->path.c_str(), O_RDONLY);
        if (_fd_body == -1) {
            this->status_code = 500;
            --_it_recipes;
            return ;
        }
    }
    if (is_fd_read_ready(_fd_body) != true || // Client and file ready?
            *this->is_write_ready != true ) {
        --_it_recipes;
        return ;
    }
    ft_bzero(buf, BUFFER_READ);
    bytes_read = read(_fd_body, buf, BUFFER_READ);
    if (bytes_read == 0 || bytes_read > 0) {
        if (send(client_fd, buf, bytes_read, 0) == -1) {
            std::cerr << "_send_respons_body : send() failed" << std::endl;
            this->status_code = 500;
            --_it_recipes;
            return ;
        }
        if (bytes_read > 0)
            --_it_recipes;
    } else if (bytes_read == -1) {
        std::cerr << "_send_respons_body : read() failed" << std::endl;
        this->status_code = 500;
        --_it_recipes;
        return ;
    }
    return ;
}

/* SEND_RESPONS()
 * Send the respons from the server to the client
 */
void                    c_callback::_send_respons(void) {
    if (g_verbose) {
        std::cout << "TASK : _send_respons()" << std::endl;
        std::cout << _resp_headers.c_str() << std::endl;
    }

    if (send(client_fd, _resp_headers.c_str(), _resp_headers.length(), 0) < 1) {
        std::cerr << "Error: Respons to client" << std::endl;
        this->status_code = 500;
    }
}

