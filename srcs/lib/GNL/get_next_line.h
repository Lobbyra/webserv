#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
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

int			get_next(int fd, char **line, const char *const sep);
int			get_next_line(int fd, char **line);
int			ft_gnl(int fd, char **line, t_gnl **alst, const char *const sep);
t_gnl		*ft_lstnew_gnl(int fd);

// From libft
size_t		ft_strlen(const char *s);

#endif
