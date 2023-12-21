/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 21:03:19 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/21 20:37:00 by sel-jett         ###   ########.fr       */
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

void ft_execute(t_pipe *pipex, char **env, int cmd, char **av)
{
	int		i;
	char	*env_var;
	char	**cmmd;

	i = 0;
	cmmd = ft_split(av[cmd], ' ');
	// dprintf(2, "%d\n", cmd);
	// dprintf(2, "%s\n", av[cmd]);
	// exit(1);
	while (pipex->path[i])
	{
		env_var = ft_strjoin("/", (ft_split(av[cmd], ' '))[0]);
		env_var = ft_strjoin(pipex->path[i], env_var);
		cmmd[0] = ft_strjoin("/", (ft_split(av[cmd], ' '))[0]);
		cmmd[0] = ft_strjoin(pipex->path[i], env_var);
		if (!access(env_var, F_OK))
		{
			if (!access(env_var, X_OK))
			{
				dprintf(2, "command == %s\n", env_var);
				if (execve(env_var, cmmd, env) == -1)
					perror("??????\n");
			}
			else
				perror(strerror(errno));
		}
		free(env_var);
		i++;
	}
	perror(strerror(errno));
}

void	ft_first_cmd(t_pipe *pipex, char **env, char **av)
{
	int	i;

	i = -1;
	// ft_init_pipe(&pipex);
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
	}
	if (dup2(pipex->fd[0][1], STDOUT_FILENO) == -1)
		perror("fd1");
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
		perror("[i - 1]");
	if (dup2(pipex->fd[i][1], STDOUT_FILENO) == -1)
		perror("fd[1]");
	i = -1;
	while (++i < (pipex->ac - 4))
	{
		ft_close(pipex->fd[i][1]);
		ft_close(pipex->fd[i][0]);
	}
	ft_execute(pipex, env, pipex->cmd, av);
}

void	ft_third_cmd(t_pipe *pipex, char **env, int cmd, char **av)
{
	int	i;

	pipex->cmd += 2;
	dprintf(2, ">>>> zbi %s <<<<", av[pipex->cmd]);
	// exit(1);
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
		perror("[i - 1]");
	if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
		perror("out fd");
	i = -1;
	while (++i < (pipex->ac - 4))
	{
		ft_close(pipex->fd[i][1]);
		ft_close(pipex->fd[i][0]);
	}
	ft_execute(pipex, env, pipex->cmd, av);
}
