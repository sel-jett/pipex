/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 04:29:21 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/05 15:50:47 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_pipe
{
	char	*path;
	char	*cmd_1;
	char	*cmd_2;
	char	**envp;
	int		in_fd;
	int		out_fd;
}	t_pipe;

#endif
