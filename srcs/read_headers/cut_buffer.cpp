#include <iostream>
#include <list>
#include <string>

#include "lib.hpp"
#include "utils.hpp"

/* DEL_NODES
 * This function will pop front elem while it is inferior in len than len char
 * we want to remove from the buffer.
 * String must be allocated in heap.
 */
static void del_nodes(std::list<char*> *buffer, unsigned int &len) {
    while (buffer->size() > 0 && len > ft_strlen(buffer->front())) {
        len -= ft_strlen(buffer->front());
        free(buffer->front());
        buffer->pop_front();
    }
}

/* CUT_BUFFER
 * This function will cut n chars from the start of the buffer.
 */
void    cut_buffer(std::list<char*> *buffer, unsigned int len) {
    char *sub_string = NULL;
    unsigned int sub_str_len;

    del_nodes(buffer, len);
    if (buffer->size() > 0) {
        sub_str_len = ft_strlen(buffer->front()) - len;
        sub_string = ft_substr(buffer->front(), len, sub_str_len);
        free(buffer->front());
        buffer->pop_front();
        if (ft_strlen(sub_string) > 0)
            buffer->push_front(sub_string);
        else
            free(sub_string);
    }
}

/* make test ; ./test & wait 2 ; leaks test ; pkill test
int         main(void) {
    std::list<char*> *buffer = new std::list<char*>();

    cut_buffer(buffer, 0);
    std::cout << " - CRASH TEST - " << std::endl;
    std::cout << "buffer->size() == " << buffer->size() << std::endl;
    cut_buffer(buffer, 1);
    std::cout << "buffer->size() == " << buffer->size() << std::endl;
    cut_buffer(buffer, 10);
    std::cout << "buffer->size() == " << buffer->size() << std::endl;
    std::cout << "-- If you this this it's ok --" << std::endl << std::endl;

    std::cout << " - ONE EMPTY STRING - " << std::endl;
    buffer->push_back(ft_strdup(""));
    std::cout << "(expected) size 1 and one empty string : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;
    cut_buffer(buffer, 0);
    std::cout << "    cut_buffer(buffer, 0)" << std::endl;
    std::cout << "(expected) size 0 and one empty string : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;
    cut_buffer(buffer, 1);
    std::cout << "    cut_buffer(buffer, 1)" << std::endl;
    std::cout << "(expected) size 0 and no string : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;
    std::cout << " - ---------------- - " << std::endl << std::endl;

    std::cout << " - ONE STRING SUBSTRACTION - " << std::endl;
    buffer->push_back(ft_strdup("123456789abcdefghijklmopqrstuvwxyz"));
    std::cout << "(expected) size 1 and one alpha-num string : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;
    cut_buffer(buffer, 0);
    std::cout << "    cut_buffer(buffer, 0)" << std::endl;
    std::cout << "(expected) size 1 and one alpha-num string : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;
    cut_buffer(buffer, 1);
    std::cout << "    cut_buffer(buffer, 1)" << std::endl;
    std::cout << "(expected) size 1 one alpha-num string - 1 : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;
    cut_buffer(buffer, 10);
    std::cout << "    cut_buffer(buffer, 10)" << std::endl;
    std::cout << "(expected) size 1 one alpha-num string - 11 : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;
    cut_buffer(buffer, 5000);
    std::cout << "    cut_buffer(buffer, 5000)" << std::endl;
    std::cout << "(expected) size 0 : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;
    std::cout << " - ONE STRING SUBSTRACTION - " << std::endl;
    std::cout << " - ----------------------- - " << std::endl << std::endl;

    std::cout << " - MANY SMALL STRINGS / MULTI NODE DELETION - " << std::endl;
    buffer->push_back(ft_strdup("petit"));
    buffer->push_back(ft_strdup("small"));
    buffer->push_back(ft_strdup("chisai"));
    buffer->push_back(ft_strdup("pequeno"));
    buffer->push_back(ft_strdup("parvus"));
    std::cout << "(expected) size 5 : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;
    cut_buffer(buffer, 15);
    std::cout << "    cut_buffer(buffer, 15)" << std::endl;
    std::cout << "(expected) size 3 : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;
    cut_buffer(buffer, 1);
    std::cout << "    cut_buffer(buffer, 1)" << std::endl;
    std::cout << "(expected) size 2 : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;
    cut_buffer(buffer, 0);
    std::cout << "    cut_buffer(buffer, 0)" << std::endl;
    std::cout << "(expected) size 2 : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;
    cut_buffer(buffer, 7);
    std::cout << "    cut_buffer(buffer, 7)" << std::endl;
    std::cout << "(expected) size 1 : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;
    cut_buffer(buffer, 1000);
    std::cout << "    cut_buffer(buffer, 1000)" << std::endl;
    std::cout << "(expected) size 0 : " << buffer->size() << " : ";
    std::cout << "buffer = " << *buffer << std::endl;

    std::cout << " - ---------------------------------------- - " << std::endl << std::endl;

    delete buffer;
    return (0);
}

__attribute__((destructor)) static void leak() {
    std::cout << "You can check if this program leaks..." << std::endl;
    getchar();
}
*/
