#include <list>
#include <iostream>

char    *concate_list_str(std::list<char*> *buffer) {
    std::list<char*>::iterator     it;
    std::list<char*>::iterator     ite;
    int                            i = 0;

    std::cout << "concate_list_str" << std::endl;
    it = buffer->begin();
    ite = buffer->end();
    while (it != ite) {
        std::cout << "Ls: " << (*it) << std::endl;
        while ((*it)[i]){
            i++;
        }
        it++;
    }
    std::cout << "I: " << i << std::endl;
    return (NULL);
}