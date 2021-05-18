#include "get_next_line.h"
#include <iostream>

t_gnl		*ft_lstnew_gnl(int fd)
{
	t_gnl	*newNode;

	if (!(newNode = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	newNode->min = 0;
	if (!(newNode->tab = (char *)malloc(sizeof(char) * BUFFER_SIZE)))
	{
		free(newNode);
		return (NULL);
	}
	if ((newNode->max = read(fd, newNode->tab, BUFFER_SIZE)) < 0)
	{
		free(newNode->tab);
		newNode->tab = NULL;
		free(newNode);
		return (NULL);
	}
	// printf("PRINTF99 [%.*s] | ret [%d]\n", newNode->max, newNode->tab, newNode->max);
	newNode->next = 0;
	return (newNode);
}

static t_gnlfdlst	*ft_addfront_fd(t_gnlfdlst **astruct, int fd)
{
	t_gnlfdlst	*newNode;

	if (!(newNode = (t_gnlfdlst *)malloc(sizeof(*newNode))))
		return (NULL);
	newNode->fd = fd;
	if (!(newNode->list = ft_lstnew_gnl(fd)))
	{
		free(newNode);
		return (NULL);
	}
	newNode->next = *astruct;
	*astruct = newNode;
	return (newNode);
}

static void	ft_total_remove_fd(t_gnlfdlst **begin_fd, t_gnlfdlst *to_delete_fd)
{
	t_gnl		*current;
	t_gnl		*then;
	t_gnlfdlst		*tmp_fd;

	if (!to_delete_fd)
		return ;
	current = to_delete_fd->list;
	while (current)
	{
		then = current->next;
		free(current->tab);
		free(current);
		current = then;
	}
	to_delete_fd->list = NULL;
	if (*begin_fd == to_delete_fd)
		*begin_fd = to_delete_fd->next;
	else
	{
		tmp_fd = *begin_fd;
		while (tmp_fd->next && tmp_fd->next != to_delete_fd)
			tmp_fd = tmp_fd->next;
		tmp_fd->next = tmp_fd->next->next;
	}
	free(to_delete_fd);
}

int			get_next(int fd, char **line, const char *const sep, e_GNL mode)
{
	int						return_value;
	static t_gnlfdlst		*begin_fd = NULL;
	t_gnlfdlst				*right_fd;

	right_fd = begin_fd;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	while (right_fd && right_fd->fd != fd)
		right_fd = right_fd->next;
	if (mode == GNL_FLUSH) {
		ft_total_remove_fd(&begin_fd, right_fd);
		return (0);
	}
	else if (mode == GNL_HAS_LINE)
		return (has_gnl_line(&right_fd->list, sep));
	else if (line == NULL || sep == NULL)
		return (-1);
	if (right_fd == NULL)
	{
		if (!ft_addfront_fd(&begin_fd, fd))
			return (-1);
		right_fd = begin_fd;
	}
	return_value = ft_gnl(fd, line, &(right_fd->list), sep);
	if (return_value == 0 || return_value == (-1))
		ft_total_remove_fd(&begin_fd, right_fd);
	std::cout << "GNL Line:" << *line << std::endl;
	return (return_value);
}

int			get_next_line(int fd, char **line)
{
	return (get_next(fd, line, "\n", GNL_READ));
}
