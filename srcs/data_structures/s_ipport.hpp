#ifndef S_IPPORT_HPP
# define S_IPPORT_HPP

# include <string>

struct  s_ipport {
    int             port;
    std::string     ip;
};

bool    operator==(s_ipport const &a, s_ipport const &b);
bool    operator!=(s_ipport const &a, s_ipport const &b);

#endif
