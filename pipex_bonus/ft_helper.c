/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 01:35:33 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/25 02:45:14 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_init_pipe(t_pipe *pipex)
{
	pipex->ac = 0;
	pipex->cmd = 0;
	pipex->in_fd = 0;
	pipex->out_fd = 0;
	pipex->path = NULL;
	pipex->pid = 0;
}

int	ft_invalid(char *cmd)
{
	write(2, "Commande Error : ", 17);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (1);
}
