# include "c_task_queue.hpp"

/*
 **    /// CONSTRUCTORS & DESTRUCTORS PART \
 */

std::list<dumb_cb::t_dumb_f>     dumb_cb::_get_get_recipe(void) {
    std::list<t_dumb_f> funs;

    funs.push_back(&dumb_cb::coucou);
    funs.push_back(&dumb_cb::salut);
    funs.push_back(&dumb_cb::bonjour);

    return (funs);
}

void    dumb_cb::_init_meth_fun() {
    _meth_funs["GET"] = _get_get_recipe();
}

dumb_cb::dumb_cb(void) {
    return ;
}

dumb_cb::dumb_cb(std::string const &method) {
    _init_meth_fun();
    _meth_funs[method] = _get_get_recipe();
    _recipes = _meth_funs[method];
    _it_recipes = _recipes.begin();
    return ;
}

dumb_cb::dumb_cb(dumb_cb const &src) {
    *this = src;
}

dumb_cb::~dumb_cb() {
    return ;
}

/*
 **    /// FUNCTION MEMBER PART \\
 */

void    dumb_cb::exec(void) {
    if (this->is_over() == false) {
        (this->*(*_it_recipes))();
        _recipes.back();
        ++_it_recipes;
    }
}

bool    dumb_cb::is_over(void) {
    return (_it_recipes == _recipes.end());
}

/*
 **    /// OPERATOR OVERLOADS PART \\
 */
dumb_cb    &dumb_cb::operator=(dumb_cb const &src) {
    _recipes = src._recipes;
    _it_recipes = src._it_recipes;
    return (*this);
}

/*
 **    /// CONSTRUCTORS & DESTRUCTORS PART \
 */
c_task_queue::c_task_queue(void) {
    return ;
}

c_task_queue::c_task_queue(c_task_queue const &src) {
    *this = src;
}

c_task_queue::~c_task_queue() {
    return ;
}

/*
 **    /// FUNCTION MEMBER PART \\
 */

void    c_task_queue::exec_task(void) {
    if (_tasks.size() == 0)
        return;
    _tasks.back()->exec();
    if (_tasks.back()->is_over() == true) {
        close(_tasks.back()->client_fd);
        delete _tasks.back();
        _tasks.pop();
        return ;
    }
    _tasks.push(_tasks.back());
    _tasks.pop();
}

void    c_task_queue::push(std::list<s_request_header> requests,
                           std::list<s_socket> *clients) {
    c_callback *cb_temp;
    std::list<s_socket>::iterator           it_clients;
    std::list<s_request_header>::iterator   it_requests;
    std::list<s_socket>::iterator           ite_clients;
    std::list<s_request_header>::iterator   ite_requests;

    it_clients = clients->begin();
    it_requests = requests.begin();
    ite_clients = clients->end();
    ite_requests = requests.end();
    while (it_clients != ite_clients && it_requests != ite_requests) {
        cb_temp = new c_callback(*it_clients, *it_requests);
        _tasks.push(cb_temp);
        while (it_clients != ite_clients && (!it_clients->client_fd \
            || !it_clients->is_read_ready || it_clients->is_header_read))
            ++it_clients;
        ++it_requests;
    }
}

/*
 **    /// OPERATOR OVERLOADS PART \\
 */
c_task_queue    &c_task_queue::operator=(c_task_queue const &src) {
    (void)src;
    return (*this);
}
