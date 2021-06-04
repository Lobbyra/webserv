#include <map>
#include <string>

#include "lib.hpp"
#include "utils.hpp"
#include "read_headers.hpp"

static void     check_request_line(std::map<std::string,void *> &req_header) {
    size_t *error_code = static_cast<size_t *>(req_header["Error"]);
    std::string *method = static_cast<std::string *>(req_header["Method"]);
    std::string *path = static_cast<std::string *>(req_header["Path"]);
    std::string *protocol = static_cast<std::string *>(req_header["Protocol"]);

    if (method->empty() == true) {
        *error_code = 400;
    } else if (path->empty() == true ||
              (ft_strncmp(path->c_str(), "/", 1) != 0)) {
        *error_code = 400;
    } else if (protocol->empty() == true) {
        *error_code = 400;
    } else if (ft_strcmp(protocol->c_str(), "HTTP/1.1") != 0) {
        *error_code = 505;
    }
}

static void    parse_protocol(std::string const &line,
                       std::string::const_iterator &it,
                       std::map<std::string, void *> &header_ptrs) {
    std::string     protocol;
    std::string     sep(" ");

    protocol = get_word(line, it, sep);
    for (; it != line.end(); ++it)
        if (sep.find(*it) != std::string::npos)
            break ;
    if (it != line.end()) {
        size_t *error_code = static_cast<size_t *>(header_ptrs["Error"]);
        *error_code = 400;
    }
    std::string * ptr = static_cast<std::string *>(header_ptrs["Protocol"]);
    *ptr = protocol;
}

static void    parse_path(std::string line,
                   std::map<std::string, void *> &header_ptrs) {
    std::string     path;
    std::string     sep(" ");
    std::size_t     found = line.find(sep);
    std::string::const_iterator it, ite;

    if (found == std::string::npos)
        return ;
    it = line.begin() + found;
    ite = line.end();
    while (it != ite && sep.find(*it) != std::string::npos)
        ++it;
    path = get_word(line, it, sep);
    if (path == *(static_cast<std::string *>(header_ptrs["Method"])))
        return ;
    std::string * ptr = static_cast<std::string *>(header_ptrs["Path"]);
    *ptr = path;
    while (it != ite && sep.find(*it) == std::string::npos)
        ++it;
    while (it != ite && sep.find(*it) != std::string::npos)
        ++it;
    parse_protocol(line, it, header_ptrs);
}

static std::list<std::string>   init_meth_names(void) {
    std::list<std::string>  meth_names_lst;

    meth_names_lst.push_back("GET");
    meth_names_lst.push_back("PUT");
    meth_names_lst.push_back("HEAD");
    meth_names_lst.push_back("POST");
    meth_names_lst.push_back("TRACE");
    meth_names_lst.push_back("DELETE");
    meth_names_lst.push_back("OPTIONS");
    return (meth_names_lst);
}

void    parse_status_line(std::string line,
                          std::map<std::string, void*> *header_ptrs) {
    std::string             prefix;
    std::string             sep(" ");
    std::list<std::string>  lst_prefix = init_meth_names();
    std::list<std::string>::iterator it = lst_prefix.begin();
    std::list<std::string>::iterator ite = lst_prefix.end();
    size_t *error_code = static_cast<size_t *>((*header_ptrs)["Error"]);

    prefix = get_word(line, line.begin(), sep);
    while (it != ite) {
        if (prefix == *it) {
            std::string * ptr = (std::string*)((*header_ptrs)["Method"]);
            *ptr = prefix;
            parse_path(line, *header_ptrs);
            break ;
        }
        ++it;
    }
    if (it == ite && prefix.empty() == false) {
        std::cout << "PREFIX:" << prefix << "|" << prefix.empty() << std::endl;
        *error_code = 405;
    } else if (it == ite && prefix.empty() == true) {
        *error_code = 400;
    } else
        check_request_line(*header_ptrs);
}
