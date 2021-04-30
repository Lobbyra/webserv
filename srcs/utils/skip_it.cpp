#include <string>

/*
 * Forward it until a char in sep is encountered
 */

void    skip_it(std::string::const_iterator &it, const std::string sep) {
    char *ite_ptr = (char*)it.operator->();

    while (*ite_ptr != '\0')
        ++ite_ptr;
    while (it.operator->() != ite_ptr && sep.find(*it) == std::string::npos) {
        ++it;
    }
}
