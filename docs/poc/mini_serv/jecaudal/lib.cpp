#include "lib.h"

static t_bool  ft_isnum(char c)
{
    if (c >= '0' && c <= '9')
        return (TRUE);
    return (FALSE);
}

static t_bool  ft_isspace(char c) {
    if (c == '\t' ||
        c == '\n' ||
        c == '\v' ||
        c == '\f' ||
        c == '\r' ||
        c == ' ')
        return (TRUE);
    return (FALSE);
}

int     ft_atoi(const char *str) {
    unsigned int i;
    unsigned int nb;
    unsigned int neg;

    i = 0;
    nb = 0;
    neg = 0;
    if (!str)
        return (0);
    while (ft_isspace(str[i]) == TRUE)
        i++;
    while (str[i] == '+' || str[i] == '-')
        if (str[i++] == '-')
            neg++;
    while (ft_isnum(str[i]) == TRUE) {
        nb = nb * 10 + (str[i] - '0');
        i++;
    }
    if (neg % 2 == 1)
        return (nb * (-1));
    else
        return (nb);
}

int     ft_strlen(char *str)
{
    char *temp = str;

    while (*temp)
        temp++;
    return (temp - str);
}

int     ft_strncmp(char *s1, char *s2, unsigned int n)
{
    char *t_s1;

    t_s1 = s1;
    while (*t_s1 == *s2 && *t_s1 != '\0' && *s2 != '\0' && t_s1 - s1 + 1 < n) {
        t_s1++;
        s2++;
    }
    return (*t_s1 - *s2);
}
