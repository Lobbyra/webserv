#include "webserv.hpp"

extern volatile bool g_run;

static void ft_signal(int sig) {
    static_cast<void>(sig);
    g_run = 0;
}

static void ft_signalhandler_enable(void) {
    signal(SIGINT, ft_signal);
}

static int  print_usage(char const *const prog_name) {
    std::cerr << "Usage: " << prog_name << " [nginx.conf]" << std::endl;
    return (1);
}

int     main(int argc, const char **argv) {
    if (argc == 1)
        argv[1] = "config_files/ok_basic.conf";
    else if (argc != 2)
        return (print_usage(argv[0]));
    std::list<c_server> conf;

    try {
        conf = parse_conf(argv[1]);
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
