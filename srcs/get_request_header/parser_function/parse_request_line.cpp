#include "../get_request_header.hpp"

void    parse_method(std::string line, 
                     std::map<std::string, void *> request_header) {
    std::string     prefix;
    std::string     sep(" ");
    std::list<std::string>  lst_prefix = init_prefix_method();
    std::list<std::string>::iterator it, ite;

    ite = lst_prefix.end();
    prefix =  get_word_it(line.begin(), sep);
    for (it = lst_prefix.begin(); it != ite; it++)
    {
        if (prefix == *it)
        {
            std::string * ptr = static_cast<std::string *>(request_header["Method"]);
            *ptr = prefix;
            parse_path(line, request_header);
            parse_protocol(line, request_header);
        }
    }
}

void    parse_path(std::string line, 
                   std::map<std::string, void *> request_header) {
    std::size_t     found = line.find(" ") + 1;
    std::string     path;
    std::string     sep(" ");

    path =  get_word_it(line.begin() + found, sep);
    std::string * ptr = static_cast<std::string *>(request_header["Path"]);
    *ptr = path;
}

void    parse_protocol(std::string line, 
                       std::map<std::string, void *> request_header) {
    std::size_t     found = line.find(" ", (line.find(" ") + 1));
    std::string::iterator       it = line.begin() + (found + 1);
    
    std::string     protocol(it, line.end());
    std::string * ptr = static_cast<std::string *>(request_header["Protocol"]);
    *ptr = protocol;
}
