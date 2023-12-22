/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:16:53 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/22 17:01:47 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdlib.h>

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < 3)
		i++;
	return (s1[i] - s2[i]);
}

char	*get_path(char **env)
{
	int		i;
	char	*pwd;

	i = 0;
	pwd = NULL;
	while (env[i])
	{
		if (!ft_strcmp(env[i], "PATH"))
		{
			pwd = env[i];
			break ;
		}
		i++;
	}
	return (pwd);
}

int	check_parsing(t_pipe *pipex, int ac, char **av)
{
	int	i;

	if (ac < 5)
		exit(1);
	i = -1;
	pipex->ac = ac;
	pipex->cmd = 2;
	pipex->in_fd = open(av[1], O_RDONLY);
	if (pipex->in_fd == -1)
		return (exit(1), 0);
	pipex->out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->out_fd == -1)
		return (ft_close(pipex->in_fd), exit(1), 0);
	pipex->fd = my_malloc(pipex, (sizeof(int *) * (ac - 3)), 1);
	while (++i < ac - 4)
		pipex->fd[i] = my_malloc(pipex, sizeof(int) * 2, 1);
	i = -1;
	while (++i < (ac - 4))
		if (pipe((pipex->fd[i])) == -1)
			perror("pipe error");
	return (0);
}

void	ft_close(int i)
{
	if (i != -1)
	{
		close(i);
		i = -1;
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pipex;
	int		i;

	(1) && (i = -1, ft_init_pipe(&pipex), check_parsing(&pipex, ac, av));
	pipex.path = ft_split(&pipex, get_path(env), ':');
	while (++i < (ac - 3))
	{
		pipex.pid = fork();
		(pipex.pid == -1) && (perror("fork error"), 0);
		if (i == 0 && pipex.pid == 0)
			ft_first_cmd(&pipex, env, av);
		else if (i < (ac - 4) && pipex.pid == 0)
			ft_second_cmds(&pipex, env, (i + 2), av);
		else if (i == (ac - 4) && pipex.pid == 0)
			ft_third_cmd(&pipex, env, (i + 2), av);
	}
	while (1)
	{
		if (waitpid(-1, NULL, 0) == -1)
			break ;
		i = -1;
		while (++i < (ac - 4))
			(1) && (ft_close(pipex.fd[i][0]), ft_close(pipex.fd[i][1]), 0);
	}
	return (my_malloc(&pipex, 0, 2), 0);
}
