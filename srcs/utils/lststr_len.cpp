#include <list>
#include <string>

size_t  lststr_len(std::list<std::string> const &lst, std::string const sep) {
    size_t result;

    result = 0;
    for (std::list<std::string>::const_iterator it = lst.begin();
            it != lst.end(); ++it) {
        result += it->size();
        result += sep.size();
    }
    return (result);
}
