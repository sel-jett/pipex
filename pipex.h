/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 04:29:21 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/25 02:12:54 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipe
{
	pid_t	pid;
	pid_t	pid2;
	int		pfd[2];
	char	**env;
	char	**cmd_1;
	char	**cmd_2;
	char	**path;
	int		in_fd;
	int		out_fd;
}	t_pipe;

typedef struct t_data
{
	void			*data;
	struct t_data	*next;
}	t_data;

void	ft_close(int i);
int		ft_invalid(char *cmd);
void	*my_malloc(t_pipe *pipex, int size, int mode);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(t_pipe *pipex, char const *s1, char const *s2);
char	**ft_split(t_pipe *pipex, char const *s, char c);
void	ft_the_work(t_pipe *pipex);
void	ft_execute(t_pipe *pipex, char **cmd);
int		main(int ac, char **av, char **env);

#endif
