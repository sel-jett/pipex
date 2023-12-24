/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:14:12 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/24 22:11:55 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execute(t_pipe *pipex, char **cmd)
{
	int		i;
	char	*env_var;

	i = 0;
	(!cmd[0]) && (write(2, "Invalid commande\n", 17), my_malloc(pipex, 0, 0), 0);
	while (pipex->path[i])
	{
		env_var = ft_strjoin(pipex, "/", cmd[0]);
		env_var = ft_strjoin(pipex, pipex->path[i], env_var);
		if (!access(env_var, F_OK))
		{
			if (!access(env_var, X_OK))
				execve(env_var, cmd, pipex->env);
			else
				perror(strerror(errno));
		}
		free(env_var);
		i++;
	}
	perror(strerror(errno));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_close(int i)
{
	if (i != -1)
	{
		close(i);
		i = -1;
	}
}

char	*ft_strjoin(t_pipe *pipex, char const *s1, char const *s2)
{
	char	*str;
	size_t	size;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = my_malloc(pipex, (sizeof(char) * (size + 1)), 1);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	size = 0;
	while (s2[size])
	{
		str[i + size] = s2[size];
		size++;
	}
	str[i + size] = '\0';
	return (str);
}

