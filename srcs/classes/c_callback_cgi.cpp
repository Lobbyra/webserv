#include <c_callback.hpp>

std::list<c_callback::t_task_f> c_callback::_init_recipe_cgi(void) {
    std::list<t_task_f> recipe;

    recipe.push_back(&c_callback::_meth_cgi_launch);
    return (recipe);
}

void    c_callback::_meth_cgi_launch(void) {
    std::cout << "_meth_cgi_launch" << std::endl;
}
