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

// Flush data in a fd
static void flush_fd(int fd) {
    get_next(fd, NULL, NULL, GNL_FLUSH);
}

// This function will remove finished request from client list
static void    remove_clients(std::list<s_socket> *clients, int client_fd) {
    std::list<s_socket>::iterator it  = clients->begin();
    std::list<s_socket>::iterator ite = clients->end();

    while (it != ite) {
        if (it->client_fd == client_fd) {
            flush_fd(client_fd);
            break ;
        }
        ++it;
    }
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
        remove_clients(_clients, front->client_fd);
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
        if (it_clients->server == NULL || it_clients->is_callback_created) {
            ++it_clients;
            continue ;
        }
        cb_temp = new c_callback(&(*it_clients), it_clients->headers, clients);
        it_clients->is_callback_created = true;
        _tasks.push(cb_temp);
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
