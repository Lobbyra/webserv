#include "c_callback.hpp"
#include <sys/time.h>

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
    headers.push_back("Server: Drunk-Architect TEAM");
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

void    c_callback::_gen_resp_headers(void) {
    std::cout << "TASK : _gen_resp_headers()" << std::endl;
    std::list<std::string> headers;

    headers.push_back(get_status_line(status_code));
    grh_add_headers(headers, *this);
    _resp_headers = lststr_to_strcont(headers, "\r\n");
    _resp_headers += "\r\n\r\n";
}

/* FD_IS_READY_TO_SEND()
 * Function which verifies that we can write in the fd
 * If not decrement the iterator it_recipes
 */
void                    c_callback::_fd_is_ready_to_send(void) {
    std::cout << "TASK : _fd_is_ready_to_send()" << std::endl;
    if (*(this->is_write_ready) == false) {
        _it_recipes--;
    }
}

/* SEND_RESPONS_BODY()
 * Send the respons body from the server to the client
 * Open the requested file, read the file, and send line by line
 */
void                    c_callback::_send_respons_body(void) {
    char            buf[512];
    int             file_fd;
    int             status;

    ft_bzero(buf, 512);
    if ((file_fd = open(this->path.c_str(), O_RDONLY)) != -1) {
        while ((status = read(file_fd, buf, 511)) > 0) {
            send(client_fd, buf, ft_strlen(buf), 0);
            ft_bzero(buf, 512);
        }
    } else {
        std::cerr << "Error: open() _gen_resp_body" << std::endl;
    }
    close(file_fd);
}

/* SEND_RESPONS()
 * Send the respons from the server to the client
 */
void                    c_callback::_send_respons(void) {
    std::cout << "TASK : _send_respons()" << std::endl;
    if (send(client_fd, _resp_headers.c_str(), _resp_headers.length(), 0) == -1) {
		std::cerr << "Error: Respons to client" << std::endl;
	} if (_resp_body == true) {
        _send_respons_body();
    }
}

