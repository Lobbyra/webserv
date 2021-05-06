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

bool    is_fd_read_ready(int fd) {
    fd_set  set;
    timeval tv;

    tv.tv_sec = 0;
    FD_ZERO(&set);
    FD_SET(fd, &set);
    select(fd + 1, &set, NULL, NULL, &tv);
    return (FD_ISSET(fd, &set));
}

bool    is_fd_write_ready(int fd) {
    fd_set  set;
    timeval tv;

    tv.tv_sec = 0;
    FD_ZERO(&set);
    FD_SET(fd, &set);
    select(fd + 1, NULL, &set, NULL, &tv);
    return (FD_ISSET(fd, &set));
}
