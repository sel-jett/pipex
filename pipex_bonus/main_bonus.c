/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:16:53 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/25 03:05:38 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdlib.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < 3)
		i++;
	return (s1[i] - s2[i]);
}

int	ft_file(char *file, int mode)
{
	if (mode)
	{
		write(2, file, ft_strlen(file));
		write(2, ": Permission denied\n", 20);
	}
	else
	{
		write(2, "no such file or directory : ", 28);
		write(2, file, ft_strlen(file));
		write(2, "\n", 1);
	}
	return (1);
}

void	ft_close(int i)
{
	if (i != -1)
	{
		close(i);
		i = -1;
	}
}

void	ft_helper(t_pipe *pipex, int ac)
{
	int	i;

	i = 0;
	while (1)
	{
		if (waitpid(-1, NULL, 0) == -1)
			break ;
		i = -1;
		while (++i < (ac - 4))
			(1) && (ft_close(pipex->fd[i][0]), ft_close(pipex->fd[i][1]), 0);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipe	pipex;
	int		i;

	(ac < 6) && (write(2, "invalid arguments\n", 18), exit(1), 0);
	if (ft_strcmp("here_doc", av[1]) != 0)
	{
		(1) && (i = -1, ft_init_pipe(&pipex), check_parsing(&pipex, ac, av));
		pipex.path = ft_split(&pipex, get_path(env), ':');
		while (++i < (ac - 3))
		{
			pipex.pid = fork();
			if (pipex.pid == -1)
				(1) && (perror("fork error"), my_malloc(&pipex, 0, 0), 0);
			if (i == 0 && pipex.pid == 0)
				ft_first_cmd(&pipex, env, av);
			else if (i < (ac - 4) && pipex.pid == 0)
				ft_second_cmds(&pipex, env, (i + 2), av);
			else if (i == (ac - 4) && pipex.pid == 0)
				ft_third_cmd(&pipex, env, (i + 2), av);
		}
		ft_helper(&pipex, ac);
	}
	else
		ft_exec_cmd(here_doc(&pipex, ac, av, env), &pipex, av, env);
	return (my_malloc(&pipex, 0, 2), 0);
}
