#include "../parse_conf.hpp"

std::string skip_k_get_value(const std::string &key,
        std::string::const_iterator &it, std::string const &sep) {
    it += key.size();
    if (*it == ';')
        throw std::logic_error("Empty value for key: " + key);
    return (get_word_it(++it, sep));
}
