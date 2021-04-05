#ifndef PARSE_CONF_HPP
# define PARSE_CONF_HPP

# include <list>
# include <string>
# include <iostream>

void    skip_param(std::string::iterator &it);
void    skip_location(std::string::iterator &it);
void    skip_server(std::string::iterator &it,
                    std::string::iterator const &end);

// LIB FUNCTIONS FROM ./lib.cpp
bool    is_space(char c);
std::list<std::string> get_keys(void);
template <typename it, typename T>
it  ft_find(it start, it end, T const &val) {
    while (start != end && *start != val)
        start++;
    return (start);
}

#endif
