/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:16:53 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/06 18:16:54 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < 3)
		i++;
	return (s1[i] - s2[i]);
}

void	ft_the_work(t_pipe pipex)
{
	pipe(pipex.pfd);
	pipex.pid = fork();

	printf("%d\n", pipex.pid);
	if (pipex.pid < 0)
		perror("Error forking");
	else if (!pipex.pid)
	{
		printf("pid 2%d\n", pipex.pid);
		close(pipex.pfd[0]);
		if (dup2(pipex.in_fd, STDIN_FILENO) == -1)
			perror(strerror(errno));
		if (dup2(pipex.pfd[1], STDOUT_FILENO) == -1)
			perror(strerror(errno));
		ft_execute(pipex.cmd_1, pipex);
		close(pipex.in_fd);
		close(pipex.pfd[1]);
	}
	else if (pipex.pid > 0)
	{
		pipex.pid = fork();
		if (!pipex.pid)
		{
			printf("pid 1 : %d\n", pipex.pid);
			close(pipex.pfd[1]);
			if (dup2(pipex.pfd[0], STDIN_FILENO) == -1)
				perror(strerror(errno));
			if (dup2(pipex.out_fd, STDOUT_FILENO) == -1)
				perror(strerror(errno));
			close(pipex.out_fd);
			ft_execute(pipex.cmd_2, pipex);
			close(pipex.pfd[0]);
		}
		else
		{
			wait(NULL);
			puts("Donne1");
			close(pipex.pfd[0]);
			close(pipex.pfd[1]);
			wait(NULL);
		}
	}
}

int main(int ac, char **av, char **env)
{
	t_pipe	pipex;
	int		i;

	if (ac == 5)
	{
		i = 0;
		pipex.in_fd = open(av[1], O_RDONLY);
		(pipex.in_fd < 0) && (perror("infile faild\n"), 0);
		pipex.out_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		(pipex.out_fd < 0) && (perror("outfile faild\n"), 0);
		pipex.cmd_1 = ft_split(av[2], ' ');
		pipex.cmd_2 = ft_split(av[3], ' ');
		while (env[i] && ft_strcmp(env[i], "PATH"))
			i++;
		(!env[i]) && (perror("Path doesn't exist!!"), 0);
		pipex.path = ft_split(env[i], ':');
		pipex.env = env;
		ft_the_work(pipex);
	}
	else
		perror("Path unfound\n");
	return (0);
}
