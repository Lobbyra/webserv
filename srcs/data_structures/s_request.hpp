#ifndef S_REQUEST_HPP
# define S_REQUEST_HPP

struct s_request_header {
        std::string                 method;
        std::string                 path;
        std::string                 protocol;
        std::string                 date;
        std::string                 host;
        std::string                 referer;
        std::string                 transfer_encoding;
        std::list<std::string>      accept_charset;
        std::list<std::string>      accept_language;
        std::list<std::string>      authorization;
        std::list<std::string>      content_type;
        std::list<std::string>      user_agent;
        size_t                      content_length;
        size_t                      error;
};

#endif
