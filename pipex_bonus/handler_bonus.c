/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:03:19 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/24 23:23:43 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_init_pipe(t_pipe *pipex)
{
	pipex->ac = 0;
	pipex->cmd = 0;
	pipex->in_fd = 0;
	pipex->out_fd = 0;
	pipex->path = NULL;
	pipex->pid = 0;
}

int ft_invalid(char *cmd)
{
	write(2, "Commande Error : ", 17);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (1);
}


void	ft_execute(t_pipe *pipex, char **env, int cmd, char **av)
{
	int		i;
	char	*env_var;
	char	**cmmd;

	i = 0;
	cmmd = ft_split(pipex, av[cmd], ' ');
	(!cmmd[0]) && (write(2, "Invalid commande\n", 17), my_malloc(pipex, 0, 0));
	env_var = cmmd[0];
	while (pipex->path[i])
	{
		if (cmmd[0][0] == '/')
			env_var = ft_strjoin(pipex, "/", (ft_split(pipex, av[cmd], ' '))[0]);
		else if (cmmd[0][0] != '.')
		{
			env_var = ft_strjoin(pipex, "/", (ft_split(pipex, av[cmd], ' '))[0]);
			env_var = ft_strjoin(pipex, pipex->path[i], env_var);
		}
		if (!access(env_var, F_OK))
		{
			if (!access(env_var, X_OK))
			{
				if (execve(env_var, cmmd, env) == -1)
					(ft_invalid(cmmd[0])) && (my_malloc(pipex, 0, 0), 0);
			}
			else
				(ft_invalid(cmmd[0])) && (my_malloc(pipex, 0, 0), 0);
		}
		i++;
	}
	(ft_invalid(cmmd[0])) && (my_malloc(pipex, 0, 0), 0);
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
	{
		perror("fd1");
		my_malloc(pipex, 0, 0);
	}
	while (++i < ((pipex->ac - 4)))
	{
		ft_close(pipex->fd[i][0]);
		ft_close(pipex->fd[i][1]);
	}
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
	ft_close(pipex->out_fd);
	ft_close(pipex->in_fd);
	i = cmd - 2;
	if (dup2(pipex->fd[i - 1][0], STDIN_FILENO) == -1)
	{
		perror("[i - 1]");
		my_malloc(pipex, 0, 0);
	}
	if (dup2(pipex->fd[i][1], STDOUT_FILENO) == -1)
	{
		perror("fd[1]");
		my_malloc(pipex, 0, 0);
	}
	i = -1;
	while (++i < (pipex->ac - 4))
	{
		ft_close(pipex->fd[i][1]);
		ft_close(pipex->fd[i][0]);
	}
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
		{
			ft_close(pipex->fd[i][0]);
			ft_close(pipex->fd[i][1]);
		}
	}
	ft_close(pipex->in_fd);
	i = cmd - 2;
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
	{
		ft_close(pipex->fd[i][1]);
		ft_close(pipex->fd[i][0]);
	}
	ft_execute(pipex, env, cmd, av);
}
