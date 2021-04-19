#include "utils.hpp"

void ft_timeval_init(struct timeval *const time, int sec, int usec) {
    ft_bzero(time, sizeof(*time));
    time->tv_sec = sec;
    time->tv_usec = usec;
}
