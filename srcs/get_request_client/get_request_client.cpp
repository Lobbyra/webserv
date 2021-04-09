#include "get_request_client.hpp"

// std::map<std::string, f_request_client>        init_map_select() {

// }


void        init_request_client(char *line, c_request_client request_client) {
    if (strncmp(line, "GET", 3) == 0)
    {
        char *tmp = strncpy(tmp, line, 3);
        request_client.method = tmp;
        std::cout << std::endl << "method : " << request_client.method << std::endl;
    }
}

int         main(void)
{
    int                     status;
    char                    *line;
    c_request_client        request_client;

    while ((status = get_next_line(0, &line)) == 1) {
        // std::cout << "LINE : " << line << std::endl;
        init_request_client(line, request_client);
        free(line);
    }
    if (status == 0)
        free(line);
    return (0);
}