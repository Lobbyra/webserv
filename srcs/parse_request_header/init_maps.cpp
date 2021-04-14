#include "parse_request.hpp"

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
    map["Accept-Charset"] = &(request->accept_charset);
    map["Accept-Language"] = &(request->accept_language);
    map["Authorization"] = &(request->authorization);
    map["Content-Type"] = &(request->content_type);
    map["Host"] = &(request->host);
    map["Port"] = &(request->port);
    map["Referer"] = &(request->referer);
    map["User-Agent"] = &(request->user_agent);
    map["Error"] = &(request->error);

    return (map);
}

std::map<std::string, f_request_header>     init_parser_request(void) {
    std::map<std::string, f_request_header>   map;

    // map["Date"] = &;
    map["Accept-Charset"] = &parse_field_list_string;
    map["Accept-Language"] = &parse_field_list_string;
    map["Authorization"] = &parse_field_list_string;
    map["Content-Type"] = &parse_field_list_string;
    map["User-Agent"] = &parse_field_list_string;
    // map["Host"] = &;
    // map["Port"] = &;
    // map["Referer"] = &;

    return (map);
}