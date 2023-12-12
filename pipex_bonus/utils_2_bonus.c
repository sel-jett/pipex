/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:16:40 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/12 18:22:41 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// void	ft_execute(char **cmd, t_pipe pipex)
// {
// 	int		i;
// 	char	*env_var;

// 	i = 0;
// 	while (pipex.path[i])
// 	{
// 		env_var = ft_strjoin("/", cmd[0]);
// 		env_var = ft_strjoin(pipex.path[i], env_var);
// 		if (!access(env_var, F_OK))
// 		{
// 			if (!access(env_var, X_OK))
// 				execve(env_var, cmd, pipex.env);
// 			else
// 				perror(strerror(errno));
// 		}
// 		free(env_var);
// 		i++;
// 	}
// 	perror(strerror(errno));
// }

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	size;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (0);
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

