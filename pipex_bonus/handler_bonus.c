/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:03:19 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/25 01:36:24 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_handler(char *env_var, char **env, char **cmmd, t_pipe *pip)
{
	if (!access(env_var, F_OK))
	{
		if (!access(env_var, X_OK))
		{
			if (execve(env_var, cmmd, env) == -1)
				(ft_invalid(cmmd[0])) && (my_malloc(pip, 0, 0), 0);
		}
		else
			(ft_invalid(cmmd[0])) && (my_malloc(pip, 0, 0), 0);
	}
}

void	ft_execute(t_pipe *pip, char **env, int cmd, char **av)
{
	int		i;
	char	*env_var;
	char	**cmmd;

	cmmd = ft_split(pip, av[cmd], ' ');
	(!cmmd[0]) && (write(2, "Invalid commande\n", 17), my_malloc(pip, 0, 0));
	(1) && (env_var = cmmd[0], i = 0, 0);
	while (pip->path[i])
	{
		if (cmmd[0][0] == '/')
			env_var = ft_strjoin(pip, "/", (ft_split(pip, av[cmd], ' '))[0]);
		else if (cmmd[0][0] != '.')
		{
			env_var = ft_strjoin(pip, "/", (ft_split(pip, av[cmd], ' '))[0]);
			env_var = ft_strjoin(pip, pip->path[i], env_var);
		}
		ft_handler(env_var, env, cmmd, pip);
		i++;
	}
	(ft_invalid(cmmd[0])) && (my_malloc(pip, 0, 0), 0);
}

void	ft_first_cmd(t_pipe *pipex, char **env, char **av)
{
	int	i;

	i = -1;
	while (++i < ((pipex->ac - 4)))
	{
		if (i == 0)
			ft_close(pipex->fd[0][0]);
		else
		{
			ft_close(pipex->fd[i][0]);
			ft_close(pipex->fd[i][1]);
		}
	}
	ft_close(pipex->out_fd);
	if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
	{
		perror("in_file");
		my_malloc(pipex, 0, 0);
	}
	if (dup2(pipex->fd[0][1], STDOUT_FILENO) == -1)
		(1) && (perror("fd1"), my_malloc(pipex, 0, 0), 0);
	while (++i < ((pipex->ac - 4)))
		(1) && (ft_close(pipex->fd[i][0]), ft_close(pipex->fd[i][1]), 0);
	ft_execute(pipex, env, pipex->cmd, av);
}

void	ft_second_cmds(t_pipe *pipex, char **env, int cmd, char **av)
{
	int	i;

	pipex->cmd++;
	i = -1;
	while (++i < ((pipex->ac - 4)))
	{
		if (i == (cmd - 2))
			ft_close(pipex->fd[i][0]);
		else if (i == (cmd - 3))
			ft_close(pipex->fd[i][1]);
		else
		{
			ft_close(pipex->fd[i][0]);
			ft_close(pipex->fd[i][1]);
		}
	}
	(i = cmd - 2) && (ft_close(pipex->out_fd), ft_close(pipex->in_fd), 0);
	if (dup2(pipex->fd[i - 1][0], STDIN_FILENO) == -1)
		(1) && (perror("[i - 1]"), my_malloc(pipex, 0, 0), 0);
	if (dup2(pipex->fd[i][1], STDOUT_FILENO) == -1)
		(1) && (perror("fd[1]"), my_malloc(pipex, 0, 0), 0);
	i = -1;
	while (++i < (pipex->ac - 4))
		(1) && (ft_close(pipex->fd[i][1]), ft_close(pipex->fd[i][0]), 0);
	ft_execute(pipex, env, cmd, av);
}

void	ft_third_cmd(t_pipe *pipex, char **env, int cmd, char **av)
{
	int	i;

	i = -1;
	while (++i < ((pipex->ac - 4)))
	{
		if (i == (cmd - 3))
			ft_close(pipex->fd[i][1]);
		else
			(1) && (ft_close(pipex->fd[i][0]), ft_close(pipex->fd[i][1]), 0);
	}
	(i = cmd - 2) && (ft_close(pipex->in_fd), 0);
	if (dup2(pipex->fd[i - 1][0], STDIN_FILENO) == -1)
	{
		perror("[i - 1]");
		my_malloc(pipex, 0, 0);
	}
	if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
	{
		perror("out fd");
		my_malloc(pipex, 0, 0);
	}
	i = -1;
	while (++i < (pipex->ac - 4))
		(1) && (ft_close(pipex->fd[i][1]), ft_close(pipex->fd[i][0]), 0);
	ft_execute(pipex, env, cmd, av);
}
