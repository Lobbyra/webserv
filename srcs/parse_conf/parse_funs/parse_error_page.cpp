#include "parse_conf.hpp"

/*
 * This function will parse an error_page line.
 *
 * It take an iterator that point on first letter of error_page
 *
 * When there is many code for one file like this :
 * error_page 501 502 503 err_5XX.html;
 * error_page jdfiuos;
 * error_page;
 *
 * It will return a map as this :
 * error_page[501] = err_5XX.html
 * error_page[502] = err_5XX.html
 * error_page[503] = err_5XX.html
 *
 * The return is design to be merged in a map cause we can have many error_page
 * call and we will save this data in one unique map.
 */

static std::map<int, std::string>   gen_map(std::list<int> codes,
                                            std::string path) {
    std::map<int, std::string>  error_pages;

    for (std::list<int>::iterator it = codes.begin(); it != codes.end(); it++) {
        error_pages.insert(std::pair<int, std::string>(*it, path));
    }
    return (error_pages);
}

static std::list<int>   get_codes(std::string::const_iterator &it) {
    std::string     tmp_word;
    std::list<int>  codes;

    tmp_word = get_word_it(it, whitespaces + ";");
    while (is_str_num(tmp_word)) {
        codes.push_back(ft_atoi(tmp_word.c_str()));
        while (is_space(*it) == false && *it != ';') // Skip the code
            ++it;
        while (is_space(*it) == true) // Skip whitespaces if exist
            ++it;
        tmp_word = get_word_it(it, whitespaces + ";");
    }
    if (codes.size() == 0)
        throw std::logic_error("error_page : no code gived");
    return (codes);
}

void    parse_error_page(std::string::const_iterator it, void *ptr) {
    std::string                 path;
    std::list<int>              codes;
    std::map<int, std::string>  *map_ptr;
    std::map<int, std::string>  tmp_map;

    it += ft_strlen("error_page");
    if (*it == ';')
        throw std::logic_error("error_page : no arguments found");
    else
        ++it;

    map_ptr = (std::map<int, std::string>*)ptr;
    codes = get_codes(it);
    path = get_word_it(it, whitespaces + ";");
    if (path.empty())
        throw std::logic_error("error_page : no page path found");
    tmp_map = gen_map(codes, path);
    map_ptr->insert(tmp_map.begin(), tmp_map.end());
}

/*
int         main(int argc, char **argv) {
    if (argc == 2) {
        std::string                 arg = argv[1];
        std::map<int, std::string>  m;

        try {
            parse_err_page(arg.begin(), (void*)&m);
            std::cout << m << std::endl;
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return (0);
}
*/
