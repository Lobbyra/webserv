#include "parse_request.hpp"

static void skip_prefix(std::string const &src,
                    std::string::const_iterator &it, const std::string sep){
    std::string::const_iterator ite = src.end();

    while (it != ite && sep.find(*it) == std::string::npos)
        ++it;
    if (it != ite)
        it++;
}

static void skip_sep(std::string const &src,
                     std::string::const_iterator &it, const std::string sep){
    std::string::const_iterator ite = src.end();

    while (it != ite && sep.find(*it) != std::string::npos)
        ++it;
}

static std::string get_param(std::string const &src,
                    std::string::const_iterator &it, std::string sep) {
    std::string::const_iterator ite = it;

    while (it != src.end() && sep.find(*it) == std::string::npos)
        it++;
    return (std::string(ite, it));
}

void    parse_field_date(std::string line, void *p) {
    std::string::const_iterator     it, ite;

    it = line.begin();
    ite = line.end();
    skip_prefix(line, it, ":");
    std::string *ptr = static_cast<std::string*>(p);
    skip_sep(line, it, " ");
    *ptr = get_param(line, it, "\0");
}

void    parse_field_size_t(std::string line, void *p) {
    std::string::const_iterator     it, ite;

    it = line.begin();
    ite = line.end();
    skip_prefix(line, it, ":");
    size_t *ptr = static_cast<size_t*>(p);
    skip_sep(line, it, " ");
    std::stringstream       sstream(get_param(line, it, ",; "));
    sstream >> *ptr;
}

void    parse_field_std_string(std::string line, void *p) {
    std::string::const_iterator     it, ite;

    it = line.begin();
    ite = line.end();
    skip_prefix(line, it, ":");
    std::string *ptr = static_cast<std::string*>(p);
    skip_sep(line, it, " ");
    *ptr = get_param(line, it, ",; ");
}


void    parse_field_list_string(std::string line, void *p) {
    std::string::const_iterator     it, ite;

    it = line.begin();
    ite = line.end();
    skip_prefix(line, it, ":");
    std::list<std::string> *ptr = static_cast<std::list<std::string>*>(p);
    while (it != ite)
    {
        skip_sep(line, it, " ");
        ptr->push_back(get_param(line, it, ",; "));
        if (it != line.end())
            it++;
    }
}

/* PARSE_REQUEST_HEADER()
 * This function parse the header in line and edit the variable in
 * s_request_header from calling function read_request_header().
 *
 * It return 1 if the line given contain an HTTP header. Return 0 else
 */
int    parse_request_header(std::string line,
                    std::map<std::string, void *> request_header,
                    std::map<std::string, f_request_header> parser_request) {
    std::string     prefix;
    std::string     sep(":");

    prefix = get_word(line, line.begin(), sep);
    if (parser_request.find(prefix) != parser_request.end()) {
        parser_request[prefix](line, request_header[prefix]);
    } else {
        return (0);
    }
    return (1);
}
