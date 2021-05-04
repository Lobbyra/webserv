#include <iostream>

#include "colors.hpp"
#include "s_request_header.hpp"
#include "insert_stream_cont.hpp"

std::ostream& operator<<(std::ostream& os, s_request_header const &src)
{
    os << COLOR_WHITE_("Request line: ") << std::endl   \
    << "Method: " << src.method << std::endl     \
    << "Path: " << src.path << std::endl         \
    << "Protocol: " << src.protocol << std::endl \
    << "Error: " << src.error << std::endl;

    os << COLOR_WHITE_("Request header: ") << std::endl;
    os << "Host: " << src.host << std::endl;
    os << "Content-Length: " << src.content_length << std::endl;
    if (src.accept_charset.size() > 0)
        os << "Accept-charset: " << src.accept_charset << std::endl;
    if (src.accept_language.size() > 0)
        os << "Accept-language: " << src.accept_language << std::endl;
    if (src.authorization.size() > 0)
        os << "Authorization: " << src.authorization << std::endl;
    if (src.content_type.size() > 0)
        os << "Content-Type: " << src.content_type << std::endl;
    if (src.user_agent.size() > 0)
        os << "User-Agent: " << src.user_agent << std::endl;
    if (src.date != "")
        os << "Date: " << src.date << std::endl;
    if (src.accept_charset.size() > 0)
        os << "Referer: " << src.referer << std::endl;
    if (src.transfer_encoding != "")
        os << "Transfer-Encoding: " << src.transfer_encoding << std::endl;
    if (src.saved_headers.size() > 0)
        os << "saved headers: " << src.saved_headers << std::endl;
    return os;
};
