/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:21:59 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/23 15:56:39 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	my_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

char	*my_strcpy(char *s1, char *s2, char *str)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	if (s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	if (s2)
	{
		while (s2[size])
		{
			str[i + size] = s2[size];
			size++;
		}
	}
	str[i + size] = '\0';
	return (str);
}

char	*ft_strjoin_get(char *s1, char *s2)
{
	char	*str;
	size_t	size;

	if (!s2)
		return (s1);
	size = my_strlen(s1) + my_strlen(s2);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str = my_strcpy(s1, s2, str);
	free(s1);
	return (str);
}

int	ft_str_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (i);
}

int	find_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
