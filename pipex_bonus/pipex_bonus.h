/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:16:47 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/22 16:51:38 by sel-jett         ###   ########.fr       */
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
int		main(int ac, char **av, char **env);
void	ft_second_cmds(t_pipe *pipex, char **env, int cmd, char **av);
void	ft_third_cmd(t_pipe *pipex, char **env, int cmd, char **av);


#endif
