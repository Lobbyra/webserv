#include <list>
#include <string>
#include <iostream>

#include "lib.hpp"

/* FIND_STR_BUFFER
 * This function return the number of chars between the start of the buffer and
 * the first char of to_find if it found in the buffer. If to_find is not found
 * in the buffer, this function return 0.
 */
unsigned int find_str_buffer(std::list<char*> *buffer, std::string to_find) {
    char const   *i_to_find = NULL;
    char const   *i_buf_parts = NULL;
    unsigned int final_len = 0;
    std::list<char*>::iterator it = buffer->begin();
    std::list<char*>::iterator ite = buffer->end();

    i_to_find = to_find.c_str();
    while (it != ite) {
        i_buf_parts = *it;
        while (*i_buf_parts) {
            if (*i_buf_parts == *i_to_find) {               // A same char saw
                ++i_to_find;
                if (*i_to_find == '\0') {                     // Find exit case
                    ++final_len;
                    return (final_len - to_find.size());
                }
            } else if (i_to_find != to_find.c_str()) {      // Find not complet
                i_to_find = to_find.c_str();
            }
            ++final_len;
            ++i_buf_parts;
        }
        ++it;
    }
    return (0);
}

/*
int         main(void) {
    std::list<char*>    buf_empty;
    std::list<char*>    buf_small;
    std::list<char*>    buf_big;
    std::list<char*>    buf_small_find;
    std::list<char*>    buf_big_find;

    std::cout << " - BUF_EMPTY - " << std::endl;
    std::cout << "expected : 0" << std::endl;
    std::cout << find_str_buffer(&buf_empty, "C") << std::endl;
    std::cout << " - --------- - " << std::endl << std::endl;

    std::cout << " - BUF_SMALL - " << std::endl;
    std::cout << "expected : 5" << std::endl;
    buf_small.push_back("small");
    std::cout << find_str_buffer(&buf_small, "C") << std::endl;
    std::cout << " - --------- - " << std::endl << std::endl;

    std::cout << " - BUF_BIG - " << std::endl;
    std::cout << "expected : 368" << std::endl;
    buf_big.push_back("Le Conseil constitutionnel a censuré jeudi le controv");
    buf_big.push_back("ersé ex-article 2493 de la loi sécurité globale, qui ");
    buf_big.push_back("instaure un délit de \"provocation à l'identification");
    buf_big.push_back("\" des membres des forces de l'ordre et limite ainsi,");
    buf_big.push_back("selon ses détracteurs, la liberté de la presse. Le mi");
    buf_big.push_back("nistre de l’Intérieur, Gérald Darmanin, proposera \"d");
    buf_big.push_back("'améliorer les dispositions\" retoquées.");
    std::cout << find_str_buffer(&buf_big, "AUTO") << std::endl;
    std::cout << " - ------- - " << std::endl << std::endl;

    std::cout << " - BUF_SMALL_FIND_CHAR - " << std::endl;
    std::cout << "expected : 9" << std::endl;
    buf_small_find.push_back("123456789");
    buf_small_find.push_back("abcdef");
    std::cout << find_str_buffer(&buf_small_find, "ab") << std::endl;
    std::cout << " - ------------------- - " << std::endl << std::endl;

    std::cout << " - BUF_BIG_FIND_CHAR - " << std::endl;
    std::cout << "expected : 297" << std::endl;
    std::cout << find_str_buffer(&buf_big, "Gérald") << std::endl;
    std::cout << " - ----------------- - " << std::endl << std::endl;
    return (0);
}
*/
