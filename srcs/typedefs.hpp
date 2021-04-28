#ifndef TYPEDEFS_HPP
# define TYPEDEFS_HPP

# include <map>
# include <list>
# include <string>

typedef std::map<int, bool>                 t_respmap;
typedef std::map<int, std::string>          t_error_page;
typedef std::map<std::string, std::string>  t_cgi_param;

typedef std::list<int>                      t_fdlst;
typedef std::list<std::string>              t_strlst;

typedef std::string::iterator               t_strit;
typedef std::string::const_iterator         t_strcit;

#endif
