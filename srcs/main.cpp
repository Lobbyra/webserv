#include "webserv.hpp"
#include "lib.hpp"

extern volatile bool g_run;
extern bool g_verbose;

static void ft_signal(int sig) {
    static_cast<void>(sig);
    g_run = 0;
}

static void ft_signalhandler_enable(void) {
    signal(SIGINT, ft_signal);
}

static int  print_usage(char const *const prog_name) {
    std::cerr << "Usage: " << prog_name << " [-v] [file.conf]" << std::endl;
    return (1);
}

int     main(int argc, const char **argv) {
    std::list<c_server> conf;

    argc = 1;
    if (argv[argc] && !ft_strcmp(argv[argc], "-v"))
        g_verbose = argc++;
    if (argv[argc] == NULL)
        argv[argc] = "config_files/methods_allowed.conf";
    else if (argv[argc + 1] != NULL)
        return (print_usage(argv[0]));

    try {
        conf = parse_conf(argv[argc]);
        std::cout << conf << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << "Error config: " << e.what() << std::endl;
        return (1);
    }
    ft_signalhandler_enable();
    webserv(conf);
    return (0);
}

/*
int         main(void) {
    int fd;
    char *buff;

    fd = open("big", O_RDONLY);
    std::cout << get_next(fd, &buff, "\r\n");
    return (0);
}
*/
