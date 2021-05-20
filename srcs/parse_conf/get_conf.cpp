
#include "webserv.hpp"

static bool    is_separator(char c) {
    return ((c == '{' || c == '}' || c == ';'));
}

// start = conf.begin(), it = point at {, keyword = the one to check;
static bool check_key(t_strcit begin, t_strcit it, std::string const keyword) {
    const t_strcit start = (--it) - keyword.size();

    if (start < begin)
        return (0);
    if (keyword.compare(std::string(start, it)) != 0)
        return (0);
    if (start - 1 >= begin && *(start - 1) != ' ')
        return (0);
    return (1);
}

static void    check_curly_braces(const std::string &conf) {
    unsigned int lbrace = 0, rbrace = 0;
    std::string::const_iterator it = conf.begin(), ite = conf.end();

    for (; it != ite; ++it) {
        if (*it == '{') {
            if (lbrace == rbrace && !check_key(conf.begin(), it, "server"))
                throw std::logic_error("get_conf: Invalid scope type");
            ++lbrace;
        }
        else if (*it == '}') {
            if (it - 2 < conf.begin() || !is_separator(*(it - 2))
                || (it + 2 < ite && *(it + 2) == '{'))
                throw std::logic_error("get_conf: Invalid end of scope");
            ++rbrace;
        }
    }
    if (lbrace != rbrace)
        throw std::logic_error("get_conf: Braces does not match");
}

static void    add_content_to_str(std::string &res, const char *line) {
    while (*line) {
        if (!res.empty() && *(--res.end()) != ' ')
            res.push_back(' ');
        while (*line && whitespaces.find(*line) == std::string::npos) {
            if (*line == '#')
                return ;
            if (is_separator(*line)) {
                if (*(--(res.end())) != ' ' && *line != ';')
                    res.push_back(' ');
                if (*(--(res.end())) == ' ' && *line == ';')
                    res.erase(--(res.end()));
                res.push_back(*line++);
                res.push_back(' ');
            }
            else
                res.push_back(*line++);
        }
        while (*line && whitespaces.find(*line) != std::string::npos)
            ++line;
    }
}

std::string    get_conf(const char *const path) {
    int             n;
    int             fd;
    char            *line;
    std::string     res;

    if ((fd = open(path, O_RDONLY)) < 0)
        throw std::logic_error("Cannot open config file");

    while ((n = get_next_line(fd, &line)) >= 1) {
        add_content_to_str(res, line);
        free(line);
    }
    if (n == 0)
        free(line);
    else if (n == -1)
        throw std::logic_error("GNL");

    close(fd);
    res.erase(--(res.end()));
    check_curly_braces(res);
    return (res);
}

/*
int        main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <nginx.conf>" << std::endl;
        return (1);
    }
    std::string conf = get_conf(argv[1]);

    std::cout << conf << std::endl;
    // check_curly_braces(conf);
    return (0);
}
*/
