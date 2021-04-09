#include "parse_conf.hpp"

/*
 * This function will take an iterator to the first letter of a location block
 * and return a structure from the context. (see /srcs/data_structures.hpp)
 * 
 * Two location type are allowed :
 * - path
 *      location PATH {}
 *      location /route/asked/by/client/ {}
 *   Normal route asked by a client. A path that not start with a / is ignored.
 *      (to be ignored, the string route will be empty)
 *   If the path is not ended by a /, this function will append one.
 *
 * - extension
 *      location ~ \EXTENSION {}
 *      location ~ \.php {}
 *   A file extension. route saved as ".php" in a string. Must 
 */

/*
 * ERROR MESSAGES
 */
#define LOC_EXT_MISS "location : extension missing"
#define LOC_NOT_W_FORMAT "location : extension not well formated"
#define LOC_ARG_MISS "location : route missing"
#define LOC_ARG_TOO_MANY "location : too many arguments"
#define LOC_KEY_NOT_CONTEXT "location : key " + key + " not valid in location"

// Get route from informations between location key word and the first {.
static std::string  get_route(std::string::iterator it) {
    it += ft_strlen("location ");
    // extension case
    if (*it == '~' && *(it + 1) == ' ') {
        it += 2; // skip "~ "

        if (*it == '{')
            throw std::logic_error(LOC_EXT_MISS);

        if (*it != '\\')
            throw std::logic_error(LOC_NOT_W_FORMAT);
        return (get_word_it(it + 1));
    }

    // path case
    std::string::iterator check_path = it;
    if (*check_path == '{')
        throw std::logic_error(LOC_ARG_MISS);
    while (is_space(*check_path) == false)
        ++check_path;
    ++check_path;
    if (*check_path != '{')
        throw std::logic_error(LOC_ARG_TOO_MANY);

    if (*it != '/')
        return ("");
    return (get_word_it(it)); 
}

// skip the part "location (~) [URI] { ". Start a 'l' of "location"
static void skip_uri(t_strit &it) {
    while (*it != '{')
        ++it;
    it += 2; // skip the "{ "
}

c_location  get_location(t_strit it) {
    c_location                      loc;
    std::string                     key;
    std::map<std::string, void*>    loc_ptr_select;
    std::map<std::string, f_parser> parse_select;

    parse_select = init_parsing_select();
    loc_ptr_select = init_loc_ptr_select(&loc);
    loc.route = get_route(it);
    skip_uri(it);
    while (*it != '}') {
        key = get_word_it(it, whitespaces + ";");
        check_key(key);
        if (key == "listen" || key == "server_name")
            throw std::logic_error(LOC_KEY_NOT_CONTEXT);
        parse_select[key](it, loc_ptr_select[key]);
        skip_param(it);
    }
    return (loc);
}

/*
int         main(int argc, char **argv) {
    if (argc == 2) {
        std::string location = argv[1];

        try {
            c_location loc = get_location(location.begin());
            std::cout << loc;
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return (0);
}
*/
