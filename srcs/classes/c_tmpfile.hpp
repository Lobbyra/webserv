#ifndef C_TMPFILE_CLASS_HPP
# define C_TMPFILE_CLASS_HPP

# include <iostream>
# include <string>
# include <unistd.h>

class c_tmpfile {
    protected:
        static const char *const    _path;
        static std::string          _nextnameprefix;
        static void                 _update_nextnameprefix(void);
        static std::string          _get_next_name(void);
        static bool                 _does_nextfile_exist(void);
        std::string                 _filename;
        int                         _fd;
        int                         _select(void) const;

    public:
        c_tmpfile(void);
        c_tmpfile(c_tmpfile const &src);
        virtual ~c_tmpfile(void);

        c_tmpfile   &operator=(c_tmpfile const &rhs);
        int const   &get_fd(void) const;
        bool        is_read_ready(void) const;
        bool        is_write_ready(void) const;
        void        reset_cursor(void);
};

std::ostream    &operator<<(std::ostream &o, c_tmpfile const &i);

#endif // ******************************************* C_TMPFILE_CLASS_HPP end //
