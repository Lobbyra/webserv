#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

enum	e_GNL {
	GNL_START,
	GNL_READ,
	GNL_FLUSH,
	GNL_HAS_LINE,
	GNL_END
};

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

int		get_next(int fd, char **line, const char *const sep, e_GNL mode = GNL_READ);
int		get_next_line(int fd, char **line);
int		ft_gnl(int fd, char **line, t_gnl **alst, const char *const sep);
t_gnl	*ft_lstnew_gnl(int fd);
bool	has_gnl_line(t_gnl const *const *alist, const char *const sep);

// From libft
size_t		ft_strlen(const char *s);

#endif
