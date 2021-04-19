#ifndef C_TASK_QUEUE_HPP
# define C_TASK_QUEUE_HPP

typedef t_dumb_f void (dumb_cb::*)(void);
typedef std::list<t_dumb_f> t_recipes;
typedef std::list<t_dumb_f>::const_iterator t_recipes_it;

std::map<std::string, std::list<t_dumb_f> > g_meth_fun;
g_meth_fun["GET"] = {&dumb_cd::coucou, &dumb_cd::salut, &dumb_cd::bonjour};

class    dumb_cb {
 public:

    dumb_cb(void);
    dumb_cb(std::string const &method);
    dumb_cb(dumb_cb const &src) { *this = src; };
    dumb_cb &operator=(dumb_cb const &src);
    virtual ~dumb_cb();

    void    exec(void);
    bool    is_over(void) { return (_it_recipes == _recipes.end()); };

    void    coucou(void) { std::cout << "coucou" << std::endl; }
    void    salut(void) { std::cout << "salut" << std::endl; }
    void    bonjour(void) { std::cout << "bonjour" << std::endl;

 private:

    t_recipes       _recipes;
    t_recipes_it    _it_recipes;

};

class    c_task_queue {
 public:

    c_task_queue(void);
    c_task_queue(c_task_queue const &src);
    c_task_queue &operator=(c_task_queue const &src);
    virtual ~c_task_queue();

    void    exec_task(void);
    void    push(std::list<s_request_header> requests,
                 std::list<s_socket> clients);


 private:
    _pop();

    std::queue<dumb_cb> _tasks; 

};

std::ostream    &operator<<(std::ostream &o, c_task_queue const &i);

#endif
