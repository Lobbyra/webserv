#ifndef C_TASK_QUEUE_HPP
# define C_TASK_QUEUE_HPP

//# include "webserv.hpp"
# include <list>
# include <queue>

# include "lib.hpp"
# include "s_socket.hpp"
# include "c_callback.hpp"
# include "s_request_header.hpp"

class    c_task_queue {
 public:

    c_task_queue(void);
    c_task_queue(c_task_queue const &src);
    c_task_queue &operator=(c_task_queue const &src);
    virtual ~c_task_queue();

    void    exec_task(void);
    void    push(std::list<s_socket> *clients);

    void    set_clients(std::list<s_socket> *clients);

 private:
    std::queue<c_callback*> _tasks;
    std::list<s_socket>     *_clients;

};

#endif
