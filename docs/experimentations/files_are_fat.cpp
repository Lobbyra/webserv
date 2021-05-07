#include <iostream>

/* FILES_ARE_FAT_CPP
 * "Yow what is this file ?"
 * Yes you probably ask this question by exploring this repo but you will
 * understand...
 *
 * Do you know how many ms a file takes to be created and be ready to be read ?
 * This file will answer to your question.
 *
 * USAGE:
 *  ./fat
 * RETURN:
 *  Nothing, this is a program. Just watch output.
 */

#include <ctime>      // gen_random()
#include <fcntl.h>    // open()
#include <errno.h>
#include <unistd.h>   // gen_random()
#include <sys/time.h>

// Return the substraction of time given and current time in micro second
unsigned int    get_time(timeval tt_start)
{
    timeval      curr;
    unsigned int time;

    gettimeofday(&curr, NULL);
    curr.tv_sec -= tt_start.tv_sec;
    time = curr.tv_sec * 1000000;
    time += curr.tv_usec - tt_start.tv_usec;
    return (time);
}

// Get the current time in usec precision
unsigned int    get_curr_time(void)
{
    timeval       curr;

    gettimeofday(&curr, NULL);
    return (curr.tv_sec * 1000000 + curr.tv_usec);
}

// Generate random string
std::string gen_random(const int len) {
    std::string tmp_s;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    srand( (unsigned) time(NULL) * getpid());
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    return tmp_s;
}

// Blocking fd measurement
void    blocking_fd(void) {
    int          fd;
    timeval      curr;
    std::string  path;
    std::string  self_path;
    unsigned int result_in_ms;

    // write
    std::cout << "blocking write on a new file take : ";
    path = "/tmp/";
    path += gen_random(10);
    gettimeofday(&curr, NULL);
    fd = open(path.c_str(), O_CREAT | O_WRONLY);
    write(fd, path.c_str(), path.size());
    result_in_ms = get_time(curr);
    std::cout << result_in_ms << "ms" << std::endl;
    close(fd);
    unlink(path.c_str());
}

// non-blocking fd measurement
void    non_blocking_fd(void) {
    int          fd;
    timeval      curr;
    std::string  path;
    std::string  self_path;
    unsigned int result_in_ms;

    // write
    errno = 0;
    std::cout << "non blocking write on a new file take : ";
    path = "/tmp/";
    path += gen_random(10);
    gettimeofday(&curr, NULL);
    fd = open(path.c_str(), O_CREAT | O_WRONLY);
    fcntl(fd, F_SETFL, O_NONBLOCK);
    write(fd, path.c_str(), path.size());
    result_in_ms = get_time(curr);
    std::cout << result_in_ms << "ms" << std::endl;
    close(fd);
    unlink(path.c_str());
    return ;
}

int         main(void) {
    blocking_fd();
    non_blocking_fd();
    return (0);
}
