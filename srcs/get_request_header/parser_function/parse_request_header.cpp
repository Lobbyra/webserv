#include "../get_request_header.hpp"

void    parse_request_header(std::string line, 
                             std::map<std::string, void *> request_header) {
    std::string     prefix;
    std::string     sep(":");
    
    prefix =  get_word_it(line.begin(), sep);
    std::cout << std::endl << "PREFIX : " << prefix << std::endl;

}