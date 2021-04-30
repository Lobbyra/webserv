#ifndef INSERT_STREAM_CONT_HPP
# define INSERT_STREAM_CONT_HPP

/*
 * File that contain all outstream redir for our containers.
 */

# include <map>
# include <list>
# include <vector>
# include <iostream>

extern int indent_lvl;

template <typename Tkey, typename Tvalue>
std::ostream    &operator<<(std::ostream &o, std::pair<Tkey, Tvalue> const &i)
{
    o << \
    "key = " << i.first << ", value = " << i.second;
    return (o);
};

template <typename Tkey, typename Tvalue>
std::ostream    &operator<<(std::ostream &o, std::map<Tkey, Tvalue> const &i)
{
    std::string indent(4 * indent_lvl, ' ');
    if (i.size() == 0)
    {
        o << "{}";
        return (o);
    }
    for (typename std::map<Tkey, Tvalue>::const_iterator it = i.begin();
         it != i.end();
         it++)
        o << indent << *it << std::endl;
    return (o);
};

template < class T >
inline std::ostream& operator<<(std::ostream& os, const std::list<T>& v)
{
    os << "{";
    for (typename std::list<T>::const_iterator it = v.begin(); it != v.end(); ++it) {
        if (it == v.begin())
            os << *it;
        else
            os << ", " << *it;
    }
    os << "}";
    return os;
}

#endif
