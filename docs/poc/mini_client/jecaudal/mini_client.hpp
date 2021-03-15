#ifndef MINI_CLIENT_HPP_
# define MINI_CLIENT_HPP_

# include <vector>
# include <string>
# include <iostream>
# include "lib.h"

struct  net_dest {
    int    ip;
    int    port;
};

# define IP_LEN_MIN 7
# define IP_LEN_MAX 15

void    mini_client(net_dest);

#endif
