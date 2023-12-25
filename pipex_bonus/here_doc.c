/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:13:12 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/25 01:34:13 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_parser(t_pipe *pipex, int ac, char **av, char **env)
{
	int	i;

	i = -1;
	ft_init_pipe(pipex);
	pipex->ac = ac;
	pipex->cmd = 3;
	pipex->out_fd = open(av[5], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (pipex->out_fd == -1)
	{
		my_malloc(pipex, 0, 0);
		return ;
	}
	pipex->path = ft_split(pipex, get_path(env), ':');
}

int	here_doc(t_pipe *pipex, int ac, char **av, char **env)
{
	char	*line;
	char	*limiter;
	int		pfd[2];

	if (pipe(pfd) == -1)
		perror("error pfd");
	here_doc_parser(pipex, ac, av, env);
	write(0, "pipe heredoc> ", ft_strlen("pipe heredoc> "));
	line = get_next_line(0);
	limiter = ft_strjoin(pipex, av[2], "\n");
	while (line && (ft_strcmp_two(limiter, line) != 0))
	{
		write(0, "pipe heredoc> ", ft_strlen("pipe heredoc> "));
		write(pfd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	return (close(pfd[1]), pfd[0]);
}

void	ft_my_exec(t_pipe *pipex, int pfd[2], char **env, char **av)
{
	pipex->pid = fork();
	if (!pipex->pid)
	{
		ft_close(pfd[1]);
		if (dup2(pfd[0], STDIN_FILENO) == -1)
			perror(strerror(errno));
		if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
			perror(strerror(errno));
		ft_close(pipex->out_fd);
		ft_close(pfd[0]);
		ft_execute(pipex, env, 4, av);
	}
	else
	{
		wait(NULL);
		ft_close(pfd[0]);
		ft_close(pfd[1]);
		wait(NULL);
	}
}

void	ft_exec_cmd(int fd, t_pipe *pipex, char **av, char **env)
{
	int	pfd[2];

	pipe(pfd);
	pipex->pid = fork();
	if (pipex->pid == 0)
	{
		pipex->in_fd = fd;
		dup2(pipex->in_fd, STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		ft_close(pfd[1]);
		ft_close(pfd[0]);
		ft_close(pipex->in_fd);
		ft_execute(pipex, env, 3, av);
	}
	else
		ft_my_exec(pipex, pfd, env, av);
}
