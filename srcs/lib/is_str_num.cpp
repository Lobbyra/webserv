#include "lib.hpp"

bool    is_str_num(std::string str) {
    for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
        if (!(*it >= '0' && *it <= '9'))
            return (false);
    }
    if (str.empty())
        return (false);
    return (true);
}
