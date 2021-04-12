#include "../get_request_header.hpp"

std::list<std::string>      init_prefix_method(void)
{
    std::list<std::string>  lst;

    lst.push_back("GET");
    lst.push_back("HEAD");
    lst.push_back("POST");
    lst.push_back("PUT");
    lst.push_back("DELETE");
    lst.push_back("CONNECT");
    lst.push_back("OPTIONS");
    lst.push_back("TRACE");
    return lst;
}


std::map<std::string, void*>     init_request_header(c_request_header *request) {
    std::map<std::string, void *>   map;

    map["Method"] = &(request->method);
    map["Path"] = &(request->path);
    map["Protocol"] = &(request->protocol);
    // map["Date"] = &(request->date);
    map["Accept_Charset"] = &(request->accept_charset);
    map["Accept_language"] = &(request->accept_language);
    map["Authorization"] = &(request->authorization);
    map["Content_language"] = &(request->content_language);
    map["Host"] = &(request->host);
    map["Port"] = &(request->port);
    map["Referer"] = &(request->referer);
    map["User_Agent"] = &(request->user_agent);

    return (map);
}

std::map<std::string, f_request_header>     init_parser_request(void) {
    std::map<std::string, f_request_header>   map;

    map["Method"] = &parse_method;
    // map["Path"] = &parse_path;
    // map["Protocol"] = &;
    // map["Date"] = &;
    // map["Accept_Charset"] = &;
    // map["Accept_language"] = &;
    // map["Authorization"] = &;
    // map["Content_language"] = &;
    // map["Host"] = &;
    // map["Port"] = &;
    // map["Referer"] = &;
    // map["User_Agent"] = &;

    return (map);
}