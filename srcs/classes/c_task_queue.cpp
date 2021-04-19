# include "c_task_queue.hpp"

extern std::map<std::string, std::list<t_dumb_f> > g_meth_fun;

/*
 **    /// CONSTRUCTORS & DESTRUCTORS PART \
 */
dumb_cb::dumb_cb(void) {
    g_meth_fun["GET"] = {&dumb_cb::coucou, &dumb_cb::salut, &dumb_cb::bonjour};
    return ;
}

dumb_cb::dumb_cb(std::string const &method)
: _recipes(g_meth_fun[method]), _it_recipes(_recipes.end()) {
    return ;
}

dumb_cb::dumb_cb(dumb_cb const &src) {
    _recipes = src._recipes;
    _it_recipes = src._it_recipes;
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
        *(_it_recipes)();
        ++_it_recipes;
    }
}

bool    dumb_cb::is_over(void) {
    return ();
}

/*
 **    /// OPERATOR OVERLOADS PART \\
 */
dumb_cb    &dumb_cb::operator=(dumb_cb const &src) {
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
    _tasks.back().exec();
    if (_tasks.back().is_over() == true) {
        delete _tasks.back();
        return ;
    }
    _tasks.push(_tasks.back());
    _tasks.pop();
}

void    c_task_queue::push(std::list<s_request_header> requests,
                           std::list<s_socket> clients) {
    dumb_cb *cb_temp;
    std::list<s_socket>::iterator           it_clients;
    std::list<s_request_header>::iterator   it_requests;
    std::list<s_socket>::iterator           ite_clients;
    std::list<s_request_header>::iterator   ite_requests;

    it_clients = clients.begin();
    it_requests = requests.begin();
    ite_clients = clients.end();
    ite_requests = requests.end();
    while (it_clients != ite_clients && it_requests != ite_requests) {
        cb_temp = new dumb_cb((*it_requests).method);
        _tasks.push(cb_temp);
        ++it_clients;
        ++it_requests;
    }
}

/*
 **    /// OPERATOR OVERLOADS PART \\
 */
c_task_queue    &c_task_queue::operator=(c_task_queue const &src) {
    return (*this);
}

