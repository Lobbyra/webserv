#include <string>

// Return a string accord to message
std::string get_status_msg(int code) {
    switch (code) {
        case 200:
            return ("OK");
        case 201:
            return ("Created");
        case 204:
            return ("No Content");
        case 403:
            return ("Forbidden");
        case 400:
            return ("Bad Request");
        case 404:
            return ("Not Found");
        case 405:
            return ("Not Allowed");
        case 500:
            return ("Internal Server Error");
    }
    return ("");
}
