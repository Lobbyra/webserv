#include "webserv.hpp"

bool    operator==(s_ipport const &a, s_ipport const &b) {
    return (a.ip == b.ip && a.port == b.port);
}
