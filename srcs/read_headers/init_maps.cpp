#include <map>
#include <list>
#include <string>

#include "read_headers.hpp"
#include "s_request_header.hpp"

std::map<std::string, void*>     init_header_ptrs(s_request_header *headers) {
    std::map<std::string, void *>   str_ptrs_map;

    str_ptrs_map["Path"] = &(headers->path);
    str_ptrs_map["Date"] = &(headers->date);
    str_ptrs_map["Host"] = &(headers->host);
    str_ptrs_map["Error"] = &(headers->error);
    str_ptrs_map["Method"] = &(headers->method);
    str_ptrs_map["Referer"] = &(headers->referer);
    str_ptrs_map["Protocol"] = &(headers->protocol);
    str_ptrs_map["User-Agent"] = &(headers->user_agent);
    str_ptrs_map["Content-Type"] = &(headers->content_type);
    str_ptrs_map["Authorization"] = &(headers->authorization);
    str_ptrs_map["Accept-Charset"] = &(headers->accept_charset);
    str_ptrs_map["Content-Length"] = &(headers->content_length);
    str_ptrs_map["Accept-Language"] = &(headers->accept_language);
    str_ptrs_map["Transfer-Encoding"] = &(headers->transfer_encoding);
    str_ptrs_map["trans_mode_saw"] = &(headers->is_transfer_mode_saw);
    return (str_ptrs_map);
}

std::map<std::string, f_request_header>     init_header_parsers(void) {
    std::map<std::string, f_request_header>   str_parsers_map;

    str_parsers_map["Date"] = &parse_field_date;
    str_parsers_map["Host"] = &parse_field_std_string;
    str_parsers_map["Referer"] = &parse_field_std_string;
    str_parsers_map["User-Agent"] = &parse_field_list_string;
    str_parsers_map["Content-Type"] = &parse_field_list_string;
    str_parsers_map["Authorization"] = &parse_field_list_string;
    str_parsers_map["Accept-Charset"] = &parse_field_list_string;
    str_parsers_map["Content-Length"] = &parse_field_size_t;
    str_parsers_map["Accept-Language"] = &parse_field_list_string;
    str_parsers_map["Transfer-Encoding"] = &parse_field_std_string;
    return (str_parsers_map);
}
