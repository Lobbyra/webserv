#include "utils.hpp"
#include "lib.hpp"

std::string get_status_line(int code) {
    char *str_code = ft_itoa(code);
    std::string code_msg = get_status_msg(code);
    std::string status_line = "HTTP/1.1 ";

    status_line += str_code;
    status_line += " ";
    status_line += code_msg;
    free(str_code);
    return (status_line);
}

/*
int         main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Bad args" << std::endl;
        return (1);
    }
    std::cout << get_status_line(ft_atoi(argv[1])) << std::endl;
    return (0);
}
*/
