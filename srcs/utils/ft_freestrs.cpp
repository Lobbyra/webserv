#include <stdlib.h>

void    ft_freestrs(char **strs) {
    char **temp = strs;

    if (strs == NULL) {
        return ;
    }
    while (*temp) {
        free(*temp);
        temp++;
    }
    free(strs);
}
