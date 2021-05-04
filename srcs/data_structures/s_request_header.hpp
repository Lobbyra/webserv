#ifndef S_REQUEST_HEADER_HPP
# define S_REQUEST_HEADER_HPP

# include <list>
# include <string>

struct s_request_header {
    size_t                 error; // var that will be status-code
    size_t                 content_length;
    std::string            method;
    std::string            path;
    std::string            protocol;
    std::string            date;
    std::string            host;
    std::string            referer;
    std::string            transfer_encoding;
    std::list<std::string> accept_charset;
    std::list<std::string> accept_language;
    std::list<std::string> authorization;
    std::list<std::string> content_type;
    std::list<std::string> user_agent;
    std::list<std::string> saved_headers;
};

std::ostream& operator<<(std::ostream& os, s_request_header const &src);

#endif
