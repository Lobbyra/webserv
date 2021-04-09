#include "get_request_header.hpp"

// std::map<std::string, f_request_header>        init_map_select() {

// }


void        init_request_header(char *line, c_request_header request_header) {
    if (strncmp(line, "GET", 3) == 0)
    {
        char *tmp = strncpy(tmp, line, 3);
        request_header.method = tmp;
        std::cout << std::endl << "method : " << request_header.method << std::endl;
    }
}

int         main(void)
{
    int                     status;
    char                    *line;
    c_request_header        request_header;

    while ((status = get_next_line(0, &line)) == 1) {
        // std::cout << "LINE : " << line << std::endl;
        init_request_header(line, request_header);
        free(line);
    }
    if (status == 0)
        free(line);
    return (0);
}