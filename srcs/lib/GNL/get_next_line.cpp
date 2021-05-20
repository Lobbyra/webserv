#include "get_next_line.h"
#include <iostream>

/* Warning:
 * The separator `sep` have to be smaller than BUFFER_SIZE
 */

static int		ft_lstsize_gnl(t_gnl *lst, int *flag)
{
	int i;
	int diff;

	i = 0;
	*flag = 1;
	while (lst)
	{
		if ((diff = lst->max - lst->min) < 0)
			return (-1);
		i += diff;
		lst = lst->next;
	}
	return (i);
}

static int	ft_sentence(t_gnl const *const *alist, const char *const sep)
{
	int		size;
	int		j = 0;
	t_gnl	tmp;
	t_gnl const	*lst;

	size = 0;
	lst = *alist;
	while (lst->next && lst->next->next)
	{
		size += lst->max - lst->min;
		lst = lst->next;
	}
	tmp = *lst;
	while (tmp.next != NULL || tmp.min < tmp.max)
	{
		if (tmp.min >= tmp.max)
			tmp = *tmp.next;
		if (tmp.tab[tmp.min] == sep[j])
			++j;
		else if (j != 0) {
			j = 0;
			continue ;
		}
		++tmp.min;
		++size;
		if (sep[j] == '\0')
			return (size - j);
	}
	return (-1);
}

static void		ft_lstclear_gnl(t_gnl **alst)
{
	t_gnl	*tmp;

	while ((*alst)->next)
	{
		tmp = (*alst);
		*alst = (*alst)->next;
		free(tmp->tab);
		free(tmp);
	}
}

static int		ft_found(t_gnl **alist, char **line, int size, int seplen)
{
	int		i;
	char	*src;
	t_gnl	*lst;

	i = 0;
	lst = *alist;
	src = lst->tab;
	if (!(*line = (char *)malloc(sizeof(char) * (size + 1))))
		return (0);
	while (i < size)
	{
		if ((lst->min >= lst->max) && lst->next)
		{
			lst = lst->next;
			src = lst->tab;
		}
		line[0][i++] = src[(lst->min)++];
	}
	line[0][i] = '\0';
	while (seplen--) {
		if (lst->min >= lst->max && lst->next)
			lst = lst->next;
		++lst->min;
	}
	ft_lstclear_gnl(alist);
	return (1);
}

int		ft_gnl(int fd, char **line, t_gnl **alist, const char *const sep)
{
	int		size;
	t_gnl	*list;
	int		called_lstsize = 0;

	list = *alist;
	while (((size = ft_sentence(alist, sep)) == -1) &&
			(list->max == BUFFER_SIZE || (fd == 0 && list->max > 0)))
	{
		if (!(list->next = ft_lstnew_gnl(fd)))
			return (-1);
		list = list->next;
	}
	size = (size != -1 ? size : ft_lstsize_gnl(*alist, &called_lstsize));
	if (ft_found(alist, line, size == -1 ? 0 : size, ft_strlen(sep)) == 0)
		return (-1);
	if (called_lstsize == 1 && size == 0)
		return (0);
	return ((size != -1 ? size + 1 : 0));
}

bool	has_gnl_line(t_gnl const *const *alist, const char *const sep) {
	if (alist == NULL)
		return (0);
	return (ft_sentence(alist, sep) == -1 ? false : true);
}

int		ft_flush_static(char **line, t_gnl **alist) {
	int garbage;
	int size = ft_lstsize_gnl(*alist, &garbage);

	static_cast<void>(garbage);
	if (ft_found(alist, line, size, 0) == 0)
		return (-1);
	return ((size != -1 ? size + 1 : 0));
}
