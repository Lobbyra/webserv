#include "c_callback.hpp"

void    c_callback::meth_get_open(void) {
    int fd = 

    errno = 0;
    open(root + path, O_RDONLY)i;
    if (errno == 0)
        return;
    switch (errno) {

    }
}
