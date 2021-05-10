#include <algorithm>

#include "parse_conf.hpp"

static bool is_method(std::string method) {
    std::list<std::string> methods;

    methods.push_back("GET");
    methods.push_back("PUT");
    methods.push_back("HEAD");
    methods.push_back("POST");
    methods.push_back("TRACE");
    methods.push_back("DELETE");
    methods.push_back("CONNECT");
    methods.push_back("OPTIONS");
    return ( find(methods.begin(), methods.end(), method) != methods.end() );
}

void    parse_methods(t_strcit it, void *ptr) {
    std::list<std::string> *methods = (std::list<std::string>*)ptr;
    std::string tmp_val;

    it += ft_strlen("methods ");
    if (*it == ';')
        throw std::logic_error("Empty value for key: methods");
    while (*it != ';') {
        tmp_val = get_word_it(it, whitespaces + ";");
        if (is_method(tmp_val) == false)
            throw std::logic_error(tmp_val + " method not known");
        methods->push_back(get_word_it(it, whitespaces + ";"));
        while (*it != ' ' && *it != ';')
            ++it;
        if (*it == ' ')
            ++it;
    }
}
