#ifndef C_TASK_QUEUE_HPP
# define C_TASK_QUEUE_HPP

# include "webserv.hpp"

class c_callback;

class c_callback;

class c_callback;

class    dumb_cb {
 public:
    typedef void (dumb_cb::*t_dumb_f)(void);
    typedef std::list<t_dumb_f>                 t_recipes;
    typedef std::list<t_dumb_f>::const_iterator t_recipes_it;

    dumb_cb(void);
    dumb_cb(std::string const &method);
    dumb_cb(dumb_cb const &src);
    dumb_cb &operator=(dumb_cb const &src);
    virtual ~dumb_cb();

    void    exec(void);
    bool    is_over(void);

    void    coucou(void) { std::cout << "coucou" << std::endl; }
    void    salut(void) { std::cout << "salut" << std::endl; }
    void    bonjour(void) { std::cout << "bonjour" << std::endl; }

 private:

    t_recipes       _recipes;
    t_recipes_it    _it_recipes;

    std::list<t_dumb_f> _get_get_recipe(void);
    void    _init_meth_fun();

    std::map<std::string, std::list<t_dumb_f> > _meth_funs;

};

class    c_task_queue {
 public:

    c_task_queue(void);
    c_task_queue(c_task_queue const &src);
    c_task_queue &operator=(c_task_queue const &src);
    virtual ~c_task_queue();

    void    exec_task(void);
    void    push(std::list<s_request_header> requests,
                 std::list<s_socket> *clients);

 private:
    std::queue<c_callback*> _tasks;

};

#endif
