/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 03:24:38 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/05 15:51:03 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main (int ac, char **av, char **envp)
{
	t_pipe	pipex;

	if (ac == 5)
	{
		pipex.in_fd = open(av[1], O_RDONLY);
		(in_fd < 0) && (perror("infile faild\n"), 0);
		pipex.out_fd = open(av[4], O_RDONLY | O_CREAT, 0664);
		(out_fd < 0) && (perror("outfile faild\n"), 0);
		pipex.cmd_1 = av[2];
		pipex.cmd2 = av[2];
		pipex.envp = envp;
	}
}
