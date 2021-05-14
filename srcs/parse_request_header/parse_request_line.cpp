#include "parse_request.hpp"

static void     check_request_line(std::map<std::string,void *> req_header) {
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
                       std::map<std::string, void *> request_header) {
    std::string     protocol;
    std::string     sep(" ");

    protocol =  get_word(line, it, sep);
    for (; it != line.end(); ++it)
        if (sep.find(*it) != std::string::npos)
            break ;
    if (it != line.end()) {
        size_t *error_code = static_cast<size_t *>(request_header["Error"]);
        *error_code = 400;
    }
    std::string * ptr = static_cast<std::string *>(request_header["Protocol"]);
    *ptr = protocol;
}

static void    parse_path(std::string line,
                   std::map<std::string, void *> request_header) {
    std::string     path;
    std::string     sep(" ");
    std::size_t     found = line.find(sep);
    std::string::const_iterator it, ite;

    if (found == std::string::npos)
        return ;
    it = line.begin() + found;
    ite = line.end();
    while (it != ite && sep.find(*it) != std::string::npos)
        ++it;;
    path =  get_word(line, it, sep);
    if (path == *(static_cast<std::string *>(request_header["Method"])))
        return ;
    std::string * ptr = static_cast<std::string *>(request_header["Path"]);
    *ptr = path;
    while (it != ite && sep.find(*it) == std::string::npos)
        ++it;
    while (it != ite && sep.find(*it) != std::string::npos)
        ++it;
    parse_protocol(line, it, request_header);
}

void    parse_method(std::string line,
                     std::map<std::string, void *> request_header) {
    std::string             prefix;
    std::string             sep(" ");
    std::list<std::string>  lst_prefix = init_prefix_method();
    std::list<std::string>::iterator it = lst_prefix.begin();
    std::list<std::string>::iterator ite = lst_prefix.end();

    prefix = get_word(line, line.begin(), sep);
    while (it != ite) {
        if (prefix == *it) {
            std::string * ptr = static_cast<std::string *>(request_header["Method"]);
            *ptr = prefix;
            parse_path(line, request_header);
            break ;
        }
        ++it;
    }
    check_request_line(request_header);
}
