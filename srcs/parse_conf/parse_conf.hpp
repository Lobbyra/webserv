#ifndef PARSE_CONF_HPP
# define PARSE_CONF_HPP

# include <list>
# include <string>
# include <iostream>
# include "../webserv.hpp"

typedef void (*f_parser)(t_strcit, void*);

c_server        get_serv(t_strcit it_conf);
std::string     get_conf(const char *const path);

// IT FORWARDING FUNCTIONS
void    skip_param(t_strcit &it);

void    check_key(std::string const &key);

// PARSING FUNCTIONS
std::string skip_k_get_value(const std::string &key,
                             std::string::const_iterator &it,
                             std::string const &sep);
void    parse_root(t_strcit it, void *ptr);
void    parse_index(t_strcit it, void *ptr);
void    parse_listen(t_strcit it, void *ptr);
void    parse_location(t_strcit it, void *ptr);
void    parse_autoindex(t_strcit it, void *ptr);
void    parse_error_page(t_strcit it, void *ptr);
void    parse_server_name(t_strcit it, void *ptr);
void    parse_fastcgi_pass(t_strcit it, void *ptr);
void    parse_fastcgi_param(t_strcit it, void *ptr);
void    parse_client_max_body_size(t_strcit it, void *ptr);

std::map<std::string, f_parser> init_parsing_select(void);
std::map<std::string, void*>    init_srv_ptr_select(c_server *srv);
std::map<std::string, void*>    init_loc_ptr_select(c_location *loc);

#endif
