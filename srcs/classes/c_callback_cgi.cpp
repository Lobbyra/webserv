#include "lib.hpp"
#include "c_callback.hpp"

/* C_CALLBACK_CGI
 * Recipe that will init all meta-variables and exec CGI.
 */

std::list<c_callback::t_task_f> c_callback::_init_recipe_cgi(void) {
    std::list<t_task_f> recipe;

    recipe.push_back(&c_callback::_meth_cgi_init_meta);
    recipe.push_back(&c_callback::_meth_cgi_init_http);
    if (this->transfer_encoding == "chunked") {
        recipe.push_back(&c_callback::_chunk_reading_size);
        recipe.push_back(&c_callback::_chunk_reading_chunk);
    }
    recipe.push_back(&c_callback::_meth_cgi_launch);
    recipe.push_back(&c_callback::_meth_cgi_wait);
    recipe.push_back(&c_callback::_meth_cgi_send_resp);
    return (recipe);
}

// Init specific var of CGI (meta-variables) in cgi_env_variables.
void    c_callback::_meth_cgi_init_meta(void) {
    std::cout << "TASK : _meth_cgi_init_meta()" << std::endl;
    char        *c_tmp;
    std::string tmp;
    std::string::iterator it_tmp;

    //AUTH_TYPE
    if (this->authorization.size() > 0) {
        tmp = "AUTH_TYPE=" + this->authorization.back();
        this->cgi_env_variables.push_back(tmp);
    }
    // CONTENT_LENGTH
    tmp = "CONTENT_LENGTH=";
    c_tmp = ft_itoa(this->content_length);
    tmp += c_tmp;
    free(c_tmp);
    this->cgi_env_variables.push_back(tmp);
    // CONTENT_TYPE
    if (this->content_type.size() > 0) {
        tmp = "CONTENT_TYPE=";
        for (std::list<std::string>::iterator it = this->content_type.begin();
             it != this->content_type.end(); ++it) {
            tmp += *it;
            if (it != this->content_type.end())
                tmp += ";";
        }
        this->cgi_env_variables.push_back(tmp);
    }
    // GATEWAY_INTERFACE
    tmp = "GATEWAY_INTERFACE=CGI/1.1";
    this->cgi_env_variables.push_back(tmp);
    // PATH_INFO
    tmp = "PATH_INFO=" + this->path;
    this->cgi_env_variables.push_back(tmp);
    // PATH_TRANSLATED
    tmp = "PATH_TRANSLATED=" + this->root + this->path;
    if (find(this->index.begin(), this->index.end(), std::string("index.php"))
            != this->index.end() && *(--this->path.end()) == '/') {
        tmp += "index.php";
    }
    this->cgi_env_variables.push_back(tmp);
    // QUERY STRING
    it_tmp = this->path.end();
    while (it_tmp != this->path.begin() && *it_tmp != '?')
        it_tmp--;
    if (*it_tmp == '?') {
        it_tmp++;
        tmp = "QUERY_STRING=";
        tmp += std::string(it_tmp, this->path.end());
        this->cgi_env_variables.push_back(tmp);
    }
    // REMOTE_ADDR
    char ip[20];
    ft_bzero(ip, 20);
    tmp = "REMOTE_ADDR=";
    tmp += inet_ntop(AF_INET, (sockaddr_in*)(&(this->client_addr)), ip, 20);
    this->cgi_env_variables.push_back(tmp);
    // REMOTE_USER
    if (this->fastcgi_param["REMOTE_USER"] != "") {
        tmp = "REMOTE_USER=";
        tmp += fastcgi_param["REMOTE_USER"];
        this->cgi_env_variables.push_back(tmp);
    }
    // REMOTE_IDENT
    if (this->fastcgi_param["REMOTE_IDENT"] != "") {
        tmp = "REMOTE_IDENT=";
        tmp += fastcgi_param["REMOTE_IDENT"];
        this->cgi_env_variables.push_back(tmp);
    }
    // REQUEST_METHOD
    tmp = "REQUEST_METHOD=";
    tmp += this->method;
    this->cgi_env_variables.push_back(tmp);
    // REQUEST_URI
    tmp = "REQUEST_URI=";
    tmp += this->path;
    this->cgi_env_variables.push_back(tmp);
    // SERVER_NAME
    tmp = "SERVER_NAME=";
    tmp += this->host;
    this->cgi_env_variables.push_back(tmp);
    // SERVER_PORT
    tmp = "SERVER_PORT=";
    c_tmp = ft_itoa(this->listen.port);
    tmp += c_tmp;
    free(c_tmp);
    this->cgi_env_variables.push_back(tmp);
    // SERVER_PROTOCOL
    this->cgi_env_variables.push_back("SERVER_PROTOCOL=HTTP/1.1");
    // SERVER_SOFTWARE
    this->cgi_env_variables.push_back("SERVER_SOFTWARE=drunkserv");
    std::cout << "cgi_env_varibles: " << std::endl;
    std::cout << this->cgi_env_variables << std::endl;
    _continue();
}

// Init additionnal var of from http request in cgi_env_variables.
void    c_callback::_meth_cgi_init_http(void) {
    std::cout << "TASK : _meth_cgi_init_http()" << std::endl;
    std::string::iterator cursor;

    for (std::list<std::string>::iterator it = this->saved_headers.begin();
         it != this->saved_headers.end(); ++it) {
        if ((cursor = find(it->begin(), it->end(), ':')) != it->end()) {
            it->replace(cursor, cursor + 2, "=");
        }
        cursor = it->begin();
        while (cursor != it->end() && *cursor != '=') { // key prepare
            if (*cursor >= 'a' && *cursor <= 'z') // UPPERCASE KEY
                *cursor -= 32;
            if (*cursor == '-') // - to _
                *cursor = '_';
            ++cursor;
        }
        *it = "HTTP_" + *it;
    }
    cgi_env_variables.insert(this->cgi_env_variables.begin(),
                    this->saved_headers.begin(), this->saved_headers.end());
    std::cout << "saved_headers:" << std::endl;
    std::cout << this->saved_headers << std::endl;
    std::cout << "cgi_env_variables:" << std::endl;
    std::cout << this->cgi_env_variables << std::endl;
    _continue();
}

void    c_callback::_meth_cgi_launch(void) {
    std::cout << "_meth_cgi_launch" << std::endl;
    int  fd_in;
    char *bin_path = NULL;
    char **envp = NULL;

    errno = 0;
    if (_out_tmpfile == NULL) {
        _out_tmpfile = new c_tmpfile();
    }
    if (_out_tmpfile->is_write_ready() == false) {
        --_it_recipes;
        return;
    }
    if (this->transfer_encoding == "chunked") {
        fd_in = _tmpfile->get_fd();
        _tmpfile->reset_cursor();
    }
    else
        fd_in = client_fd;
    if ((_pid = fork()) == 0) { // CHILD
        bin_path = ft_strdup(this->fastcgi_pass.c_str());
        envp = lststr_to_strs(this->cgi_env_variables);
        // TODO : DESTROY C_TASK_QUEUE
        if (bin_path == NULL || envp == NULL) {
            if (bin_path != NULL)
                free(bin_path);
            if (envp != NULL)
                ft_freestrs(envp);
            exit(1);
        }
        if (dup2(fd_in, 0) == -1 || dup2(_out_tmpfile->get_fd(), 1) == -1) {
            free(bin_path);
            ft_freestrs(envp);
            std::cerr << "cgi_launch : dup2 : " << strerror(errno) << std::endl;
        }
        if (execve(bin_path, envp, envp) == -1) {
            free(bin_path);
            ft_freestrs(envp);
            std::cerr << "cgi_launch : execv : " << strerror(errno) << std::endl;
            exit(1);
        }
    } else if (_pid == -1) { // ERROR
        std::cerr << "cgi_launch : fork : " << strerror(errno) << std::endl;
        this->status_code = 500;
    }
}

void    c_callback::_meth_cgi_wait(void) {
    std::cout << "TASK : _meth_cgi_wait" << std::endl;
    int status;
    pid_t dead;

    errno = 0;
    dead = waitpid(_pid, &status, WNOHANG);
    if (dead == -1) {
        std::cerr << "error : waitpid() : " << strerror(errno) << std::endl;
        this->status_code = 500;
        delete _tmpfile;
        delete _out_tmpfile;
        return ;
    } else if (dead == _pid) {
        _out_tmpfile->reset_cursor();
        if (this->transfer_encoding == "chunked")
            delete _tmpfile;
    } else if (dead == 0) {
        --_it_recipes;
    }
}

void    c_callback::_meth_cgi_send_resp(void) {
    std::cout << "TASK : _meth_cgi_send_resp" << std::endl;
    char *buf;

    if (_out_tmpfile->is_read_ready() == false ||
            this->is_write_ready == false) {
        --_it_recipes;
        return ;
    }
    while (get_next_line(_out_tmpfile->get_fd(), &buf) == 1) {
        send(this->client_fd, buf, ft_strlen(buf), 0);
        free(buf);
    }
    free(buf);
    delete _out_tmpfile;
}
