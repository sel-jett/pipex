/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:16:53 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/21 20:53:10 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdlib.h>

static int ft_strcmp(char *s1, char *s2)
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
			// puts(pwd);
			break ;
		}
		i++;
	}
	return (pwd);
}

int	check_parsing(t_pipe *pipex, int ac, char **av)
{
	if (ac < 5)
		exit(1);
	pipex->ac = ac;
	pipex->cmd = 2;
	pipex->in_fd = open("file.txt", O_RDONLY);
	if (pipex->in_fd == -1)
		exit(1);
	pipex->out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->out_fd == -1)
		exit(1);

	pipex->fd = calloc(sizeof(int), (ac - 3));
	if (!pipex->fd)
    	return (free(pipex->fd), exit(1), 0);
	int	i = -1;
	while (++i < ac - 4)
		pipex->fd[i] = malloc(sizeof(int) * 2);

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

	ft_init_pipe(&pipex);
	check_parsing(&pipex, ac, av);
	pipex.path = ft_split(get_path(env), ':');
	i = -1;
	while (++i < (ac - 4))
	{
		dprintf(2, "%d\n", pipe((pipex.fd[i])));
		// if (pipe((pipex.fd[i])) == -1)
		// 	perror("pipe error");
	}
	i = -1;
	while (++i < (ac - 3))
	{
		if ((pipex.pid = fork()) == -1)
			perror("fork error");
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
		{
			ft_close(pipex.fd[i][0]);
			ft_close(pipex.fd[i][1]);
		}
	}
	ft_close(pipex.out_fd);
	ft_close(pipex.in_fd);

	return (0);
}
