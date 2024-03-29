#include <string>

#include "utils.hpp"

/*
 * This function return the word from it to the next char in the sep string.
 *
 * sep = whitespace -> default
 */

std::string get_word_it(std::string::const_iterator it, const std::string sep) {
    std::string::const_iterator ite = it;

    skip_it(ite, sep);
    return (std::string(it, ite));
}

/*
int        main(void)
{
    std::string str = "lol mdrxd qweqwe";
    std::string::iterator it;

    it = str.begin();
    std::cout << get_word_it(it) << std::endl;

    it = it + 3;
    std::cout << get_word_it(it) << std::endl;

    ++it;
    std::cout << get_word_it(it) << std::endl;
    return (0);
}
*/
