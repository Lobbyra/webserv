#include <sys/time.h>
#include <sys/select.h>
#include <iostream>

/* IS_FD_READY
 *
 * RETURN :
 * Return a boolean if a fd is ready to be ready or write.
 *
 * WARNING :
 * Do not use it on sockets
 */

/* Returns:
 * 0 no operation ready
 * 1 if read_ready
 * 2 if write_ready
 * 3 if both ready
 */
static int  _select_fd(int fd) {
    fd_set  r_fdset;
    fd_set  w_fdset;
    int     res = 0;
    timeval tv = {0, 0};

    FD_ZERO(&r_fdset); FD_ZERO(&w_fdset);
    FD_SET(fd, &r_fdset); FD_SET(fd, &w_fdset);
    select(fd + 1, &r_fdset, &w_fdset, NULL, &tv);
    errno = 0;
    if (FD_ISSET(fd, &r_fdset))
        res |= 1;
    if (FD_ISSET(fd, &w_fdset))
        res |= 2;
    return (res);
}

bool    is_fd_read_ready(int fd) {
    return (_select_fd(fd) & 1);
}

bool    is_fd_write_ready(int fd) {
    return (_select_fd(fd) & 2);
}
