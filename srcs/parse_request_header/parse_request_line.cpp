#include "parse_request_header.hpp"

static void    parse_protocol(std::string const &line,
                       std::string::const_iterator &it,
                       std::map<std::string, void *> request_header) {
    std::string     protocol;
    std::string     sep(" ");   

    protocol =  get_word(line, it, sep);
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
        ++it;;
    parse_protocol(line, it, request_header);
}

static size_t     check_request_line(std::map<std::string,
                                     void *> request_header) {
    if (((static_cast<std::string *>(request_header["Method"]))->length()) <= 0)
        return (400);
    else if (((static_cast<std::string *>(request_header["Path"]))->length()) <= 0)
        return (400);
    else if (((static_cast<std::string *>
    (request_header["Protocol"]))->length()) <= 0)
        return (400);
    return (0);
}

void    parse_method(std::string line, 
                     std::map<std::string, void *> request_header) {
    std::string             prefix;
    std::string             sep(" ");
    std::list<std::string>  lst_prefix = init_prefix_method();
    std::list<std::string>::iterator it, ite;

    prefix =  get_word(line, line.begin(), sep);
    for (it = lst_prefix.begin(); it != ite; it++)
    {
        if (prefix == *it)
        {
            std::string * ptr = static_cast<std::string *>
            (request_header["Method"]);
            *ptr = prefix;
            parse_path(line, request_header);
            break ;
        }
    }
    size_t * ptr = static_cast<size_t *>(request_header["Error"]);
    *ptr = check_request_line(request_header);
}