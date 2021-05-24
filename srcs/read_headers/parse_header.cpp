#include "read_headers.hpp"
#include "utils.hpp"

/* CHECK_IF_HOST_EXIST()
 * This function check if Host header is already saved. Host header duplication
 * cause 400;
 */
static int  check_if_host_exist(std::string prefix, void *p) {
    if (prefix == "Host") {
        std::string *ptr = static_cast<std::string*>(p);
        if (ptr->empty() == false)
            return (1);
    }
    return (0);
}

/* PARSE_REQUEST_HEADER()
 * This function parse the header in line and edit the variable in
 * s_request_header from calling function read_request_header().
 *
 * It return 1 if the line given contain an HTTP header. Return 0 else
 */
int    parse_header(std::string line,
                    std::map<std::string, void *> *header_ptrs,
                    std::map<std::string, f_request_header> *header_parsers) {
    std::string     prefix;
    std::string     sep(":");

    prefix = get_word(line, line.begin(), sep);
    if (header_parsers->find(prefix) != header_parsers->end()) {
        if ((check_if_host_exist(prefix, (*header_ptrs)[prefix]) == 1))
            return (1);
        else
            (*header_parsers)[prefix](line, (*header_ptrs)[prefix]);
    }
    return (0);
}
