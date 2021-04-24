#include "utils.hpp"

std::string get_word(std::string const &src, std::string::const_iterator it,
                     std::string sep) {
    std::string::const_iterator ite = it;

    while (ite != src.end() && sep.find(*ite) == std::string::npos)
        ite++;
    return (std::string(it, ite));
}
