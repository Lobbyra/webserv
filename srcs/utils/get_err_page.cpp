#include "lib.hpp"
#include "utils.hpp"

#define TEMPLATE "<html>\r\n"                                               \
                 "<head><title>CODE MSG</title></head>\r\n"                 \
                 "<body><center><h1>CODE MSG</h1></center>\r\n"             \
                 "<hr><center>Drunk-Architect TEAM</center></body>\r\n"     \
                 "</html>\r\n"
#define MSG_LEN 3
#define CODE_LEN 4

/* GET_ERR_PAGE
 * generate the HTML page to give error to the client.
 */
std::string get_err_page(int code) {
    char        *str_code = ft_itoa(code);
    size_t      cursor = 0;
    std::string page = TEMPLATE;
    std::string status_message = get_status_msg(code);

    while ((cursor = page.find("CODE")) != std::string::npos) {
        page.replace(cursor, CODE_LEN, str_code);
    }
    while ((cursor = page.find("MSG")) != std::string::npos) {
        page.replace(cursor, MSG_LEN, status_message);
    }
    free(str_code);
    return (page);
}

/*
int         main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Bad args" << std::endl;
        return (1);
    }
    std::cout << get_err_page(ft_atoi(argv[1])) << std::endl;
    return (0);
}
*/
