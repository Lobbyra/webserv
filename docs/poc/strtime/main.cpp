// POC strXtime
//
// FUNCTIONS
//      strftime strptime gettimeofday
//
// DESCRIPTION
//      The f and p variations are for Format and Parse.
//      - Format transform a time structure in a string according to the
//        specified format.
//
//      - Parse transform a string in time structure according to specified
//        format.
//
// USAGE
//      ./strtime --format [format]
//          -> transform the current time in the specified format.
//
//      ./strtime --parse [time string] [format]
//          -> print the structure created according to given args

#include <iostream>

#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>

void    print_usage(void) {
    std::cout <<                                                         \
    "USAGE :" << std::endl <<                                            \
    "    ./strtime --format [format]" << std::endl <<                    \
    "        -> transform the current time in the specified format." <<  \
    std::endl << std::endl <<                                            \
    "    ./strtime --parse [time string] [format]" << std::endl <<       \
    "        -> print the structure created according to given args." << \
    std::endl;
}

void        strtime_format(char *format) {
    struct timeval  curr_time;
    char            result[100];

    errno = 0;
    bzero(result, 100);
    if (gettimeofday(&curr_time, NULL) == -1) {
        std::cout << "error GTD : " << strerror(errno) << std::endl;
        exit(1);
    }
    if (strftime(result, 100, format, localtime(&(curr_time.tv_sec))) == 0) {
        std::cout << "error strftime : " << strerror(errno) << std::endl;
        exit(1);
    }
    std::cout << "Current time in your format is " << result << std::endl;
}

void        strtime_parse(char *str_time, char *format) {
    struct tm  parsed_tm;

    bzero(&parsed_tm, sizeof(timeval));
    if (strptime(str_time, format, &parsed_tm) == NULL) {
        std::cout << "error strptime" << std::endl;
        exit(1);
    }
    std::cout <<                                             \
    "Your string parsed :" << std::endl <<                   \
    "  Seconds = " << parsed_tm.tm_sec << std::endl <<       \
    "  Minutes = " << parsed_tm.tm_min << std::endl <<       \
    "  Hours = " << parsed_tm.tm_hour << std::endl <<        \
    "  Day = " << parsed_tm.tm_mday << std::endl <<          \
    "  Month = " << parsed_tm.tm_mon << std::endl <<         \
    "  Year = " << parsed_tm.tm_year << std::endl <<         \
    "  Day of week = " << parsed_tm.tm_wday << std::endl <<  \
    "  Days in year = " << parsed_tm.tm_yday << std::endl << \
    std::endl;
    return;
}

int         main(int argc, char **argv) {
    if (argc != 3 && argc != 4) {
        print_usage();
        return (1);
    }
    if (strcmp(argv[1], "--format") == 0 && argc == 3) {
        strtime_format(argv[2]);
    } else if (strcmp(argv[1], "--parse") == 0 && argc == 4) {
        strtime_parse(argv[2], argv[3]);
    } else {
        std::cout << "Wrong arguments !" << std::endl << std::endl;
        print_usage();
        return (1);
    }
    return (0);
}
