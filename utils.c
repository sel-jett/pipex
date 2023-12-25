/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:49:53 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/25 02:40:34 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_invalid(char *cmd)
{
	write(2, "Commande Error : ", 17);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (1);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize)
	{
		while ((i + 1) < dstsize && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			continue ;
		}
		count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static	char	**ft_fill_str(t_pipe *pipex, char **str, char const *s, char c)
{
	int	i;
	int	pos;
	int	calc;

	i = 0;
	pos = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue ;
		}
		calc = i;
		while (s[i] && s[i] != c)
			i++;
		str[pos] = my_malloc(pipex, (sizeof(char) * (i - calc + 1)), 1);
		ft_strlcpy(str[pos], (s + calc), (i - calc + 1));
		pos++;
	}
	str[pos] = NULL;
	return (str);
}

char	**ft_split(t_pipe *pipex, char const *s, char c)
{
	int		words;
	char	**str;

	if (!s)
		return (0);
	words = count_words(s, c);
	str = my_malloc(pipex, (sizeof(char *) * (words + 1)), 1);
	ft_fill_str(pipex, str, s, c);
	return (str);
}
