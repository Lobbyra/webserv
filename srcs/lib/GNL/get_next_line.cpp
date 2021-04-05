/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 23:32:08 by mli               #+#    #+#             */
/*   Updated: 2020/01/06 18:18:52 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_lstsize_gnl(t_gnl *lst)
{
	int i;

	i = 1;
	while (lst)
	{
		i += lst->max - lst->min;
		lst = lst->next;
	}
	return (i);
}

int		ft_sentence(t_gnl **alist, int min, int max)
{
	int		size;
	char	*tab;
	t_gnl	*lst;

	size = 0;
	lst = *alist;
	while (lst->next)
	{
		size += lst->max - lst->min;
		lst = lst->next;
	}
	tab = lst->tab;
	while (min < max)
	{
		size++;
		if (tab[min++] == '\n')
			return (size);
	}
	return (0);
}

int		ft_found(t_gnl **alist, char **line, int size)
{
	int		i;
	char	*src;
	t_gnl	*lst;

	i = 0;
	lst = *alist;
	src = lst->tab;
	if (!(*line = (char *)malloc(sizeof(char) * size)))
		return (0);
	while (i < size - 1)
	{
		if ((lst->min >= lst->max) && lst->next)
		{
			lst = lst->next;
			src = lst->tab;
		}
		line[0][i++] = src[(lst->min)++];
	}
	if (lst->min >= lst->max && lst->next)
		lst = lst->next;
	line[0][i] = '\0';
	(lst->min)++;
	ft_lstclear_gnl(alist);
	return (1);
}

int		ft_gnl(int fd, char **line, t_gnl **alist)
{
	int		size;
	t_gnl	*list;

	list = *alist;
	while (((size = ft_sentence(alist, list->min, list->max)) == 0) &&
			(list->max == BUFFER_SIZE || (fd == 0 && list->max > 0)))
	{
		if (!(list->next = ft_lstnew_gnl(fd)))
			return (-1);
		list = list->next;
	}
	size = (size > 0 ? size : ft_lstsize_gnl(*alist));
	if (ft_found(alist, line, size) == 0)
		return (-1);
	return ((size > 0 ? 1 : 0));
}
