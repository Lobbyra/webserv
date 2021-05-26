#include <list>
#include <iostream>
#include <stdlib.h>

char    *concate_list_str(std::list<char*> *buffer) {
    std::list<char*>::iterator     it;
    std::list<char*>::iterator     ite;
    int                            i = 0;
    char                           *tmp;

    std::cout << "concate_list_str" << std::endl;
    it = buffer->begin();
    ite = buffer->end();
    for (;it != ite; ++it) {
        std::cout << "Ls: " << (*it) << std::endl;
        while ((*it)[i]){
            i++;
        }
    }
    if (!(tmp = (char *)malloc(sizeof(char) * (i + 1))))
        return (NULL);
    it = buffer->begin();
    i = 0;
    for (; it != ite; ++it) {
          while ((*it)[i]){
            tmp[i] = (*it)[i];
            i++;
        }
        free((*it));
        tmp[i] = '\0';
    }
    buffer->clear();
    std::cout << "I: " << i << std::endl;
    std::cout << "tmp: " << tmp << std::endl;
    return (tmp);
}