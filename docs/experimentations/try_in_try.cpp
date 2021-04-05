/*
 * Can we try inside a try ?
 */

#include <exception>
#include <iostream>

int         main(void) {
    try {
        try {
            throw std::logic_error("coucou");
        } catch (std::exception &e) {
            std::cerr << "2 :" << e.what() << std::endl;
        }
    } catch (std::exception &e) {
        std::cerr << "1 :"  << e.what() << std::endl;
    }
    return (0);
}
