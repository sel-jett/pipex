/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 04:29:21 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/06 10:48:18 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipe
{
	pid_t	pid;
	int		pfd[2];
	char	**env;
	char	**cmd_1;
	char	**cmd_2;
	char	**path;
	int		in_fd;
	int		out_fd;
}	t_pipe;

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_execute(char **cmd, t_pipe pipex);
int	main(int ac, char **av, char **env);


#endif
