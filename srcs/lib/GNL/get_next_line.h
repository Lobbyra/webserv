#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

typedef struct	s_gnl
{
	int				min;
	int				max;
	char			*tab;
	struct s_gnl	*next;
}				t_gnl;

typedef struct	s_gnlfdlst
{
	int					fd;
	t_gnl				*list;
	struct s_gnlfdlst	*next;
}				t_gnlfdlst;

int				get_next_line(int fd, char **line);
int				ft_gnl(int fd, char **line, t_gnl **alst);
t_gnl			*ft_lstnew_gnl(int fd);

#endif
