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
    free (str_content_length);
    return (str_cl);
}


static std::string get_date(void) {
    struct timeval  curr_time;
    char            result[100];

    errno = 0;
    bzero(result, 100);
    if (gettimeofday(&curr_time, NULL) == -1) {
        throw std::logic_error("get_time_of_day() failed");
    }
    if (strftime(result, 100, HTTP_DATE_FORMAT, localtime(&(curr_time.tv_sec)))
           == 0) {
        throw std::logic_error("strftime() failed");
    }
    return (result);
}

static void grh_add_headers(std::list<std::string> &headers, c_callback &cb) {
    // SERVER
    headers.push_back("Server: drunkserv");
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
    std::list<std::string> headers;

    headers.push_back(get_status_line(status_code));
    grh_add_headers(headers, *this);
    _resp_headers = lststr_to_strcont(headers, "\r\n");
    _resp_headers += "\r\n\r\n";
}

