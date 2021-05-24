#include <list>
#include <iostream>

bool        is_sep_header(std::list<char*> *buffer) {
    char *i_buf_parts = NULL;
    std::string crlf_save = "";
    std::list<char*>::iterator it = buffer->begin();
    std::list<char*>::iterator ite = buffer->end();

    while (it != ite && crlf_save != "\r\n\r\n") {
        i_buf_parts = *it;
        while (*i_buf_parts && crlf_save != "\r\n\r\n") {
            if (*i_buf_parts == '\r' || *i_buf_parts == '\n')
                crlf_save += *i_buf_parts;
            else
                crlf_save.clear();
            ++i_buf_parts;
        }
        ++it;
    }
    return (crlf_save == "\r\n\r\n");
}

/* MAIN TESTS
int n_test = 0;

void        test(bool expected, std::list<char*> *buffer) {
    std::cout << \
        "test " << n_test++ << std::endl <<                                 \
        "expected : [" << std::boolalpha << expected << "]" << std::endl << \
        "result   : [" << std::boolalpha << is_sep_header(buffer) << "]" << \
    std::endl << std::endl;
}

int         main(void) {
    std::list<char*>    buffer;

    test(false, &buffer);

    buffer.push_back("coucou");
    test(false, &buffer);

    buffer.push_back("salut mec ca va ?");
    buffer.push_back("");
    buffer.push_back("bah ouai trkl");
    test(false, &buffer);

    buffer.push_back("\r\n");
    buffer.push_back("GET / HTTP/1.1");
    test(false, &buffer);

    buffer.push_back("\r\n\rh\r\n\n\r");
    buffer.push_back("localhost: Host\r\n");
    test(false, &buffer);

    buffer.push_back("\r");
    buffer.push_back("\n<html>hey</html>");
    test(true, &buffer);

    buffer.clear();
    buffer.push_back("PUT /oui HTTP/1.1\r\nContent\r\n-Len: 6\r\n\r\ncoucou");
    test(true, &buffer);
    return (0);
}
*/
