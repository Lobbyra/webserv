#include "parse_request.hpp"

static void skip_prefix(std::string const &src,
                        std::string::const_iterator &it, const std::string sep) {
    std::string::const_iterator ite = src.end();

    while (it != ite && sep.find(*it) == std::string::npos)
        ++it;
    it++;
    it++;
}

static void skip_sep(std::string const &src,
                        std::string::const_iterator &it, const std::string sep) {
    std::string::const_iterator ite = src.end();

    while (it != ite && sep.find(*it) != std::string::npos)
        ++it;
}

static std::string get_param(std::string const &src, std::string::const_iterator &it,
std::string sep) {
    std::string::const_iterator ite = it;

    while (it != src.end() && sep.find(*it) == std::string::npos)
        it++;
    return (std::string(ite, it));
}


void    parse_field_list_string(std::string line, 
                             void *p) {
    std::string::const_iterator     it, ite;

    it = line.begin();
    ite = line.end();
    skip_prefix(line, it, ":");
    std::list<std::string> *ptr = static_cast<std::list<std::string>*>(p);
    while (it != ite)
    {
        skip_sep(line, it, " ");
        ptr->push_back(get_param(line, it, ",; "));
        if (it != line.end())
            it++;
    }
}

void    parse_request_header(std::string line, 
                             std::map<std::string, void *> request_header,
                             std::map<std::string, f_request_header> 
                             parser_request) {
    std::string     prefix;
    std::string     sep(":");
    
    prefix =  get_word(line, line.begin(), sep);
    if (parser_request.find(prefix) != parser_request.end())
        parser_request[prefix](line, request_header[prefix]);
    else
    {
        std::cout << "NO " << std::endl;
    }
}