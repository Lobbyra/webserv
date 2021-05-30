# include "c_task_queue.hpp"
extern bool g_verbose;

c_task_queue::c_task_queue(void) {
    return ;
}

c_task_queue::c_task_queue(c_task_queue const &src) {
    *this = src;
}

c_task_queue::~c_task_queue() {
    return ;
}

size_t   c_task_queue::size(void) const {
    return (_tasks.size());
}

// Will execute the last task in the queue and remove it if the recipe is done
void    c_task_queue::exec_task(void) {
    if (g_verbose)
        std::cout << "C_TASK_QUEUE : exec_task()" << std::endl;

    _tasks.front()->exec();
    if (_tasks.front()->is_over() == true)
        delete _tasks.front();             // Ended task deletion
    else
        _tasks.push(_tasks.front());       // Push executed task to call back
    _tasks.pop();                          // Delete task executed
}

// Add a new request in c_callback form in the queue
void    c_task_queue::push(std::list<s_socket> *clients) {
    c_callback *cb_temp = NULL;
    std::list<s_socket>::iterator it_clients = clients->begin();
    std::list<s_socket>::iterator ite_clients = clients->end();

    while (it_clients != ite_clients) {
        if (it_clients->is_header_read && !it_clients->is_callback_created &&
                it_clients->is_cache_resp == false) {
            cb_temp = new c_callback(&(*it_clients),
                    &(it_clients->headers), clients);
            it_clients->is_callback_created = true;
            _tasks.push(cb_temp);
        }
        ++it_clients;
    }
}

// Add client list to the queue
void    c_task_queue::set_clients(std::list<s_socket> *clients) {
    _clients = clients;
}

/*
 **    /// OPERATOR OVERLOADS PART \\
 */
c_task_queue    &c_task_queue::operator=(c_task_queue const &src) {
    (void)src;
    return (*this);
}
