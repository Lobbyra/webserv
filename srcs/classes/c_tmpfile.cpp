#include "c_tmpfile.hpp"
#include "colors.hpp"
#include "utils.hpp"
#include <sys/stat.h>
#include <fcntl.h>

c_tmpfile::c_tmpfile(void) : _fd(-1) {
    mkdir(c_tmpfile::_path, 0777);
    if (errno != 0 && errno != EEXIST)
        ft_error("c_tmpfile: mkdir");
    errno = 0;
    while (c_tmpfile::_does_nextfile_exist())
        c_tmpfile::_update_nextnameprefix();
    this->_filename = c_tmpfile::_get_next_name();
    this->_fd = open(_filename.c_str(), O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
    if (errno != 0)
        ft_error("c_tmpfile: open");
}

c_tmpfile::c_tmpfile(c_tmpfile const &src) {
    *this = src;
}

c_tmpfile::~c_tmpfile(void) {
    if (this->_fd == -1)
        return ;
    close(this->_fd);
    unlink(this->_filename.c_str());
}

c_tmpfile   &c_tmpfile::operator=(c_tmpfile const &rhs) {
    if (this == &rhs)
        return (*this);
    this->_filename = rhs._filename;
    this->_fd = rhs._fd;
    return (*this);
}

std::ostream    &operator<<(std::ostream &o, c_tmpfile const &i) {
    o << "{";

    o << COLOR_WHITE_("fd") << " = " << i.get_fd();
    o << COLOR_WHITE_(", is_read_ready") << " = " << \
        std::boolalpha << COLOR_BOOL_(i.is_read_ready());
    o << COLOR_WHITE_(", is_write_ready") << " = " << \
        std::boolalpha << COLOR_BOOL_(i.is_write_ready());

    o << "}" << std::endl;
    return (o);
}

int const   &c_tmpfile::get_fd(void) const { return (this->_fd); }

std::string const   &c_tmpfile::get_filename(void) const {
    return (this->_filename);
}

bool    c_tmpfile::is_read_ready(void) const {
    return (is_fd_read_ready(this->_fd));
}

bool    c_tmpfile::is_write_ready(void) const {
    return (is_fd_write_ready(this->_fd));
}

void    c_tmpfile::reset_cursor(void) {
    if (lseek(this->_fd, 0, SEEK_SET) != -1)
        return ;
    ft_error("lseek");
}

void    c_tmpfile::_update_nextnameprefix(void) {
    std::string::iterator last = --c_tmpfile::_nextnameprefix.end();

    if (c_tmpfile::_nextnameprefix.size() == 80)
        c_tmpfile::_nextnameprefix = 'A';
    else if (*last == 'Z')
        c_tmpfile::_nextnameprefix += 'A';
    else
        ++(*last);
}

bool    c_tmpfile::_does_nextfile_exist(void) {
    struct stat     buff;
    std::string     nextfile = c_tmpfile::_get_next_name();

    stat(nextfile.c_str(), &buff);
    if (errno == 0)
        return (true);
    if (errno != ENOENT)
        ft_error("stat");
    errno = 0;
    return (false);
}

std::string c_tmpfile::_get_next_name(void) {
    return (c_tmpfile::_path + c_tmpfile::_nextnameprefix + ".tmp");
}

const char *const   c_tmpfile::_path = "/tmp/webserv_tmp/";
std::string         c_tmpfile::_nextnameprefix = "A";

/*
int     main(void)
{
    while (1) {
        {
            std::cout << "c_tmpfile exist" << std::endl;
            c_tmpfile hey;
            sleep(3);
        }
        std::cout << "c_tmpfile deleted" << std::endl;
        sleep(3);
    }
    return (0);
}
*/
