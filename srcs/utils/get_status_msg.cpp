#include <string>

static std::string  msg_successful(int code) {
    switch (code) {
        case 100:
            return ("Continue");
        case 101:
            return ("Switching Protols");
        case 200:
            return ("OK");
        case 201:
            return ("Created");
        case 202:
            return ("Accepted");
        case 203:
            return ("Non-Authoritative Information");
        case 204:
            return ("No Content");
        case 205:
            return ("Reset Content");
        case 206:
            return ("Partial Content");
    }
    return ("");
}

static std::string  msg_redirection_error(int code) {
    switch (code) {
        case 301:
            return ("Moved Permanently");
        case 302:
            return ("Found");
        case 303:
            return ("See Other");
        case 304:
            return ("Not Modified");
        case 305:
            return ("Use Proxy");
        case 307:
            return ("Temporary Redirect");
    }
    return ("");
}

static std::string  msg_client_error(int code) {
    switch (code) {
        case 400:
            return ("Bad Request");
        case 401:
            return ("Unauthorized");
        case 402:
            return ("Bad Request");
        case 403:
            return ("Forbidden");
        case 404:
            return ("Not Found");
        case 405:
            return ("Not Allowed");
        case 406:
            return ("Not Acceptable");
        case 407:
            return ("Proxy Authentication Required");
        case 408:
            return ("Request Timeout");
        case 409:
            return ("Conflict");
        case 410:
            return ("Gone");
        case 411:
            return ("Length Required");
        case 412:
            return ("Precondition Failed");
        case 413:
            return ("Payload Too Large");
        case 414:
            return ("URI Too Long");
        case 415:
            return ("Unsupported Media Type");
        case 416:
            return ("Range Not Satisfiable");
        case 417:
            return ("Expectation Failed");
        case 426:
            return ("Upgrade Required");
    }
    return ("");
}

static std::string  msg_server_error(int code) {
    switch (code) {
        case 500:
            return ("Internal Server Error");
        case 501:
            return ("Not Implemented");
        case 502:
            return ("Bad Gateway");
        case 503:
            return ("Service Unavailable");
        case 504:
            return ("Gateway Timeout");
        case 505:
            return ("HTTP Version Not Supported");
    }
    return ("");
}

// Return a string accord to message
std::string get_status_msg(int code) {
    if (code / 100 == 1 || code / 100 == 2)
        return (msg_successful(code));
    else if (code / 100 == 3)
        return (msg_redirection_error(code));
    else if (code / 100 == 4)
        return (msg_client_error(code));
    else if (code / 100 == 5)
        return (msg_server_error(code));
    return ("");
}
