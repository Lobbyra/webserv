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

// Will execute the last task in the queue and remove it if the recipe is done
void    c_task_queue::exec_task(void) {
    c_callback *front;

    if (g_verbose)
        std::cout << "C_TASK_QUEUE : exec_task()" << std::endl;
    if (_tasks.size() == 0)
        return;
    front = _tasks.front();
    front->exec();

    if (front->is_over() == true) {
        reset_socket(front->client);
        _tasks.pop();
        delete front;
        return ;
    }
    _tasks.push(front);
    _tasks.pop();
}

// Add a new request in c_callback form in the queue
void    c_task_queue::push(std::list<s_socket> *clients) {
    c_callback *cb_temp = NULL;
    std::list<s_socket>::iterator it_clients = clients->begin();
    std::list<s_socket>::iterator ite_clients = clients->end();

    while (it_clients != ite_clients) {
        if (it_clients->is_header_read && !it_clients->is_callback_created) {
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
