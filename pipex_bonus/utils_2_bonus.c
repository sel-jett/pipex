/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:16:40 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/22 16:49:56 by sel-jett         ###   ########.fr       */
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
