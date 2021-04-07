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

// Get route from informations between location key word and the first {.
static std::string  get_route(std::string::iterator it) {
    std::string key_location = "location ";

    it += key_location.size(); // skip location key
    // extension case
    if (*it == '~' && *(it + 1) == ' ') {
        it += 2; // skip "~ "

        if (*it == '{')
            throw std::logic_error("location : extension missing");

        if (*it != '\\')
            throw std::logic_error("location : extension not well formated");
        return (get_word_it(it + 1));
    }

    // path case
    std::string::iterator check_path = it;
    while (is_space(*check_path) == false)
        ++check_path;
    ++check_path;
    if (*check_path != '{')
        throw std::logic_error("location : too many arguments");

    if (*it != '/')
        return ("");
    return (get_word_it(it)); 
}

// void    get_location(std::string::iterator it) {
// }

int         main(int argc, char **argv) {
    if (argc == 2) {
        std::string location = argv[1];

        try {
            std::cout << get_route(location.begin()) << std::endl;
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return (0);
}
