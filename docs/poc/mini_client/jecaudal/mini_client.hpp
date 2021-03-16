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

void    mini_client(net_dest);

#endif
