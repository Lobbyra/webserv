#include "getconf.hpp"

void    check_curly_braces(const std::string &conf) {
    unsigned int lbrace = 0, rbrace = 0;
    std::string::const_iterator it = conf.begin(), ite = conf.end();

    for (; it != ite; ++it) {
        if (*it == '{')
            ++lbrace;
        else if (*it == '}')
            ++rbrace;
    }
    if (lbrace != rbrace)
        throw std::logic_error("GetConfig: Braces does not match");
}
