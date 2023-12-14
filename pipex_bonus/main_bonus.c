/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:16:53 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/13 21:12:30 by sel-jett         ###   ########.fr       */
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


void	ft_the_work(t_pipe pipex, int i, char *env_var)
{
		pipex.pfd[i] = malloc(sizeof(int) * 2);
		if (!pipex.pfd[i])
			return ;
		pipe(pipex.pfd[i]);
		if (i == 0)
		{
			close(pipex.pfd[i][1]);
			if (dup2(pipex.in_fd, STDIN_FILENO) == -1)
				perror("strerror(errno) 1");
			if (dup2(pipex.pfd[i][0], STDOUT_FILENO) == -1)
				perror("strerror(errno) 2");
			puts("zbuba f ker l3ezwa");
			if (!access(env_var, F_OK))
			{
				if (!access(env_var, X_OK))
				{
					puts("zbuba f ker l3ezwa");
					execve(env_var, pipex.cmd[0], pipex.env);
				}
				else
					perror(strerror(errno));
			}
		}
		else if (i == (pipex.ac - 1))
		{
			close(pipex.pfd[i - 1][1]);
			if (dup2(pipex.pfd[i - 1][0], STDIN_FILENO) == -1)
				perror("strerror(errno) 3");
			if (dup2(pipex.out_fd, STDOUT_FILENO) == -1)
				perror("strerror(errno) 4");
			if (!access(env_var, F_OK))
			{
				if (!access(env_var, X_OK))
				{
					puts("zbuba f ker l3ezwa");
					execve(env_var, pipex.cmd[2], pipex.env);
				}
				else
					perror(strerror(errno));
			}
		}
		else
		{
			close(pipex.pfd[i-1][1]);
			close(pipex.pfd[i][0]);
			if (dup2(pipex.pfd[i-1][0], STDIN_FILENO) == -1)
				perror("strerror(errno) 5");
			if (dup2(pipex.pfd[i][1], STDOUT_FILENO) == -1)
				perror("strerror(errno) 6");
			if (!access(env_var, F_OK))
			{
				if (!access(env_var, X_OK))
				{
					execve(env_var, pipex.cmd[1], pipex.env);
				}
				else
					perror(strerror(errno));
			}
		}
}

void	ft_execute(t_pipe pipex)
{
	int		i;
	int		j;
	char	*env_var;
	// char	*cmd;

	j = 0;
	pipex.pfd = malloc((pipex.ac - 1) * sizeof(int *));
	if (!pipex.pfd)
		return ;
	// cmd = NULL;
	// while (pipex.cmd[j])
	// {
	// 	i = 0;
	// 	while (pipex.cmd[j][i])
	// 	{
	// 		cmd = ft_strjoin(cmd, pipex.cmd[j][i]);
	// 		i++;
	// 	}
	// 	j++;
	// }
	// puts(cmd);
	int	k = 0;
	while (pipex.cmd[j])
	{
		i = 0;
		while (pipex.path[i])
		{
			pipex.pid = fork();
			if (pipex.pid == 0)
			{
				k = 0;
				// puts(pipex.cmd[i][0]);
				while (pipex.cmd[i][k])
				{
					env_var = ft_strjoin("/", *(pipex.cmd[j]));
					k++;
				}
				env_var = ft_strjoin(pipex.path[i], env_var);
				puts(env_var);
				ft_the_work(pipex, i, env_var);
				free(env_var);
				env_var = NULL;
			}
			i++;
		}
		j++;
	}
	perror(strerror(errno));
}

int main(int ac, char **av, char **env)
{
	t_pipe	pipex;
	int		i;
	int		j;
	int		k;

	if (ac > 4)
	{
		i = 0;
		j = 2;
		k = 0;
		pipex.in_fd = open(av[1], O_RDONLY);
		(pipex.in_fd < 0) && (perror("infile faild\n"), 0);
		pipex.out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		(pipex.out_fd < 0) && (perror("outfile faild\n"), 0);
		pipex.cmd = (char ***)malloc((ac - 1) * sizeof(char **));
		if (!pipex.cmd)
			return (1);
		pipex.ac = ac;
		while (j < (ac - 1))
		{
			pipex.cmd[k] = &av[j];
			puts(*pipex.cmd[k]);
			j++;
			k++;
		}
		while (env[i] && ft_strcmp(env[i], "PATH"))
			i++;
		(!env[i]) && (perror("Path doesn't exist!!"), 0);
		pipex.path = ft_split(env[i], ':');
		pipex.env = env;
		puts("dkhlat");
		ft_execute(pipex);
		puts("Makherjat");
		// k = 0;
		// while (pipex.cmd[k])
		// 	printf("%s\n", *pipex.cmd[k++]);
	}
	else
		perror("Path unfound\n");
	j = 0;
	while (j < (pipex.ac - 3))
	{
		wait(NULL);
		j++;
	}
	return (0);
}
