/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:14:12 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/25 02:12:37 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_execute(t_pipe *pipex, char **cmd)
{
	int		i;
	char	*env_var;

	i = 0;
	if (!cmd[0])
		(1) && (write(2, "Invalid commande\n", 17), my_malloc(pipex, 0, 0), 0);
	env_var = cmd[0];
	while (pipex->path[i])
	{
		if (cmd[0][0] == '/')
			env_var = ft_strjoin(pipex, "/", cmd[0]);
		else if (cmd[0][0] != '.')
		{
			env_var = ft_strjoin(pipex, "/", cmd[0]);
			env_var = ft_strjoin(pipex, pipex->path[i], env_var);
		}
		ft_handler(env_var, pipex->env, cmd, pipex);
		i++;
	}
	(ft_invalid(cmd[0])) && (my_malloc(pipex, 0, 0), 0);
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
