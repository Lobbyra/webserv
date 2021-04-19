#ifndef C_TASK_QUEUE_HPP
# define C_TASK_QUEUE_HPP

# include "c_task_queue.hpp"
# include "dumb_cb.hpp"

extern g_meth_fun;

/*
 **    /// CONSTRUCTORS & DESTRUCTORS PART \
 */
dumb_cb::dumb_cb(void) {
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

td::ostream    &operator<<(std::ostream &o, dumb_cb const &i) {
    o /*<< DATA*/ << std::endl;
    return (o);
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
    if (_tasks.back().is_over() == false)
        _tasks.push(_tasks.back());
    _tasks._pop();
}

void    c_task_queue::push(std::list<s_request_header> requests,
                           std::list<s_socket> clients) {
    dumb_cb *cb_temp;
    std::list<s_socket>::iterator           it_clients;
    std::list<s_request_header>::iterator   it_requests;

    it_clients = 
}

/*
 **    /// OPERATOR OVERLOADS PART \\
 */
c_task_queue    &c_task_queue::operator=(c_task_queue const &src) {
    return (*this);
}

std::ostream    &operator<<(std::ostream &o, c_task_queue const &i) {
    o /*<< DATA*/ << std::endl;
    return (o);
}

#endif
