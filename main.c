/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 03:24:38 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/25 02:03:11 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < 3)
		i++;
	return (s1[i] - s2[i]);
}

void	ft_helper(t_pipe *pipex)
{
	pipex->pid = fork();
	if (!pipex->pid)
	{
		ft_close(pipex->pfd[1]);
		if (dup2(pipex->pfd[0], STDIN_FILENO) == -1)
			perror(strerror(errno));
		if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
			perror(strerror(errno));
		ft_close(pipex->out_fd);
		ft_execute(pipex, pipex->cmd_2);
		ft_close(pipex->pfd[0]);
	}
	else
	{
		wait(NULL);
		ft_close(pipex->pfd[0]);
		ft_close(pipex->pfd[1]);
		wait(NULL);
	}
}

void	ft_the_work(t_pipe *pipex)
{
	pipe(pipex->pfd);
	pipex->pid = fork();
	if (pipex->pid < 0)
		perror("Error forking");
	else if (!pipex->pid)
	{
		ft_close(pipex->pfd[0]);
		if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
			perror(strerror(errno));
		if (dup2(pipex->pfd[1], STDOUT_FILENO) == -1)
			perror(strerror(errno));
		ft_execute(pipex, pipex->cmd_1);
		ft_close(pipex->in_fd);
		ft_close(pipex->pfd[1]);
	}
	else if (pipex->pid > 0)
		ft_helper(pipex);
}

int	ft_file(char *file)
{
	write(2, "no such file or directory : ", 28);
	write(2, file, ft_strlen(file));
	write(2, "\n", 1);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pipex;
	int		i;

	if (ac == 5)
	{
		i = 0;
		pipex.in_fd = open(av[1], O_RDONLY);
		(pipex.in_fd < 0) && (ft_file(av[1]), exit(1), 0);
		pipex.out_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (pipex.out_fd < 0)
			(1) && (ft_close(pipex.in_fd), ft_file(av[ac - 1]), exit(1), 0);
		pipex.cmd_1 = ft_split(&pipex, av[2], ' ');
		pipex.cmd_2 = ft_split(&pipex, av[3], ' ');
		while (env[i] && ft_strcmp(env[i], "PATH"))
			i++;
		(!env[i]) && (perror("Path doesn't exist!!"), my_malloc(&pipex, 0, 0), 0);
		pipex.path = ft_split(&pipex, env[i], ':');
		pipex.env = env;
		ft_the_work(&pipex);
	}
	else
		perror("Path unfound\n");
	return (my_malloc(&pipex, 0, 0), 0);
}
