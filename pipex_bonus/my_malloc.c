/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jett <sel-jett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:47:54 by sel-jett          #+#    #+#             */
/*   Updated: 2023/12/22 16:26:31 by sel-jett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	dataclear(t_data **head)
{
	t_data	*temp;
	t_data	*ptr;

	if (!head || !*head)
		return ;
	temp = *head;
	while (temp)
	{
		ptr = temp->next;
		free(temp->data);
		free(temp);
		temp = ptr;
	}
	*head = NULL;
}

void	ft_close_all(t_pipe *pipex, int mode)
{
	int	i;

	i = -1;
	if (mode)
	{
		while (++i < (pipex->ac - 4))
		{
			ft_close(pipex->fd[i][0]);
			ft_close(pipex->fd[i][1]);
		}
	}
	ft_close(pipex->in_fd);
	ft_close(pipex->out_fd);
}

void	*my_malloc(t_pipe *pipex, int size, int mode)
{
	static t_data	*head;
	t_data			*node;
	void			*data;

	if (mode == 1)
	{
		data = malloc(size);
		if (!data)
			return (dataclear(&head), ft_close_all(pipex, 1), exit(1), NULL);
		node = malloc(sizeof(t_data));
		if (!node)
			return (dataclear(&head), ft_close_all(pipex, 1), exit(1), NULL);
		node->data = data;
		node->next = NULL;
		if (head)
			node->next = head;
		head = node;
		return (data);
	}
	if (!mode)
		return (dataclear(&head), ft_close_all(pipex, 1), exit(1), NULL);
	return (dataclear(&head), ft_close_all(pipex, 0), exit(1), NULL);
}
