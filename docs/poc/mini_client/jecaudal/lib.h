#ifndef LIB_H_
# define LIB_H_

# include <arpa/inet.h>
# include "get_next_line.h"

typedef char t_bool;

# define FALSE 0
# define TRUE 1

int     ft_atoi(const char *str);
int     ft_strlen(char *str);
int     ft_strncmp(const char *s1, const char *s2, unsigned int n);

#endif
