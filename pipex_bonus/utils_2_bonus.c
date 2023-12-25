/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:16:40 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/25 03:07:23 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(t_pipe *pipex, char const *s1, char const *s2)
{
	char	*str;
	size_t	size;
	size_t	i;

	size = ft_strlen(s1) + ft_strlen(s2);
	str = my_malloc(pipex, (sizeof(char) * (size + 1)), 1);
	size = 0;
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	while (s2[size])
	{
		str[i + size] = s2[size];
		size++;
	}
	str[i + size] = '\0';
	return (str);
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
		(1) && (ft_file(av[1], 0), 0);
	pipex->out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->out_fd == -1)
		return (ft_close(pipex->in_fd), ft_file(av[ac - 1], 1), exit(1), 0);
	pipex->fd = my_malloc(pipex, (sizeof(int *) * (ac - 3)), 1);
	while (++i < ac - 4)
		pipex->fd[i] = my_malloc(pipex, sizeof(int) * 2, 1);
	i = -1;
	while (++i < (ac - 4))
		if (pipe((pipex->fd[i])) == -1)
			(1) && (perror("pipe error"), my_malloc(pipex, 0, 0));
	return (0);
}
