/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecaudal <jecaudal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:22:13 by jecaudal          #+#    #+#             */
/*   Updated: 2021/03/15 14:15:05 by jecaudal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_strdup_c(char *str, char c)
{
    int     i;
    char    *result;

    i = 0;
    if (!(result = (char*)malloc(sizeof(char) * (ft_strlen_c(str, c) + 1))))
        return (NULL);
    while (str && str[i] && str[i] != c) {
        result[i] = str[i];
        i++;
    }
    result[i] = '\0';
    return (result);
}

char    *ft_strcut_c(char *str, char c)
{
    int     i;

    i = 0;
    if (!(str))
        return (NULL);
    if (is_a_c(str, c) == 0)
        return (NULL);
    while (str[i] != c)
        i++;
    i++;
    return (ft_strdup_c(&str[i], '\0'));
}

char    *ft_strjoin(char *s1, char *s2)
{
    int     i;
    int     j;
    char    *result;

    i = 0;
    j = 0;
    if (!(result = (char*)malloc(sizeof(char) *
        ((ft_strlen_c(s1, '\0') + ft_strlen_c(s2, '\0') + 1)))))
        return (NULL);
    while (s1[i]) {
        result[i] = s1[i];
        i++;
    }
    while (s2[j])
        result[i++] = s2[j++];
    result[i] = '\0';
    free(s1);
    return (result);
}
