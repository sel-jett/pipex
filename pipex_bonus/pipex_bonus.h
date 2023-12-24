/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:16:47 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/24 18:42:48 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_pipe
{
	pid_t	pid;
	int		ac;
	int		**fd;
	char	**path;
	int		cmd;
	int		in_fd;
	int		out_fd;
}	t_pipe;

typedef struct t_data
{
	void			*data;
	struct t_data	*next;
}	t_data;

char	*get_path(char **env);
int		ft_strcmp_two(char *s1, char *s2);
void	ft_close(int i);
void	ft_close_all(t_pipe *pipex, int mode);
void	*my_malloc(t_pipe *pipex, int size, int mode);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(t_pipe *pipex, char const *s1, char const *s2);
char	**ft_split(t_pipe *pipex, char const *s, char c);
void	ft_the_work(t_pipe pipex, int i, char *env_var);
void	ft_init_pipe(t_pipe *pipex);
void	ft_first_cmd(t_pipe *pipex, char **env, char **av);
// void	ft_first_cmd(t_pipe pipex, char **env, int cmd, char **av);
// void	ft_execute(t_pipe pipex);
void	ft_execute(t_pipe *pipex, char **env, int cmd, char **av);
int		here_doc(t_pipe *pipex, int ac, char **av, char **env);
void	ft_exec_cmd(int fd, t_pipe *pipex, char **av, char **env);
void	ft_second_cmds(t_pipe *pipex, char **env, int cmd, char **av);
void	ft_third_cmd(t_pipe *pipex, char **env, int cmd, char **av);
size_t	my_strlen(char *str);
char	*my_strcpy(char *s1, char *s2, char *str);
char	*ft_strjoin_get(char *s1, char *s2);
char	*ft_read_all(int fd, char *str);
char	*get_next_line(int fd);
int		find_line(char *str);
char	*get_the_line(char *str);
char	*get_the_rest(char *str, size_t size);
int		ft_str_line(char *str);


#endif
