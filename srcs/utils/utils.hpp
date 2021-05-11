#ifndef UTILS_HPP
# define UTILS_HPP

# include <list>
# include <string>
# include <iostream>

# include <errno.h>
# include <string.h>
# include <stdlib.h>

# include "insert_stream_cont.hpp"

/* # GENERAL DECLARATIONS */
const std::string whitespaces("\t\n\v\f\r ");

std::string ft_basename(std::string const path);

void    ft_error(std::string const &src,
                 std::string const &err = strerror(errno));

/* ## TRANSFORMATION FUNCTIONS */
char        *strcont_to_str(std::string str);
char        *lststr_to_str(std::list<std::string> const &lst, std::string sep);
std::string lststr_to_strcont(std::list<std::string> const &lst,
                              std::string sep);
unsigned int     hextodec(char const *hexa);

bool    is_space(char c);
bool    is_fd_read_ready(int fd);
bool    is_fd_write_ready(int fd);
bool    is_str_num(std::string str);
bool    ft_isin(const char &c, const std::string &str);

/* ## ITERATOR FUNCTIONS */
void    skip_it(std::string::const_iterator &it,
                const std::string sep = whitespaces);

std::string get_word(std::string const &src, std::string::const_iterator it,
                     std::string sep = whitespaces);

std::string get_word_it(std::string::const_iterator it,
                        const std::string sep = whitespaces);
template <typename it, typename T>
it  ft_find(it start, it end, T const &val) {
    while (start != end && *start != val)
        start++;
    return (start);
}

size_t  lststr_len(std::list<std::string> const &lst, std::string const sep);

/* ## C FUNCTIONS */
void    ft_freestrs(char **strs);
void    print_strs(char **strs, std::string sep);
char    **lststr_to_strs(std::list<std::string> lst);

/* # WEBSERV DECLARATIONS */

std::list<std::string> get_keys(void);
std::list<std::string> gen_listening(std::string dir_path);

std::string get_err_page(int code);
std::string get_status_msg(int code);
std::string get_status_line(int code);

#endif
