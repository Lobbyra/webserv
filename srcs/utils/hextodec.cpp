#include "lib.hpp"

static char ft_toupper(char c) {
    if (c >= 'a' && c <= 'z')
        return (c - 32);
    return (c);
}

static int ft_pow(int n, unsigned int pow) {
    int result;

    result = 1;
    while (pow > 0) {
        result *= n;
        --pow;
    }
    return (result);
}

static int getdecfromchar(char c) {
    char *i_ptr;
    char hex_chars[] = "0123456789ABCDEF";

    i_ptr = hex_chars;
    while (*i_ptr) {
        if (*i_ptr == c)
            return (i_ptr - hex_chars);
        ++i_ptr;
    }
    return (0);
}

unsigned int hextodec(char const *hexa) {
    unsigned int pow;
    unsigned int result;
    char const *tmp;

    pow = 0;
    tmp = hexa;
    result = 0;
    while (*tmp)
        ++tmp;
    if (*tmp == '\0')
        --tmp;
    while (tmp >= hexa) {
        result += getdecfromchar(ft_toupper(*tmp)) * ft_pow(16, pow);
        --tmp;
        ++pow;
    }
    return (result);
}

/*
#include <iostream>
int         main(void) {
    std::string hexa;

    hexa = "f";
    std::cout << "f in dec = " << hextodec(hexa.c_str()) << std::endl;
    hexa = "0";
    std::cout << "0 in dec = " << hextodec(hexa.c_str()) << std::endl;
    hexa = "34635";
    std::cout << "34635 in dec = " << hextodec(hexa.c_str()) << std::endl;
    return (0);
}
*/
