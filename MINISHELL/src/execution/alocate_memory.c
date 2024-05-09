/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alocate_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:45:54 by mafurnic          #+#    #+#             */
/*   Updated: 2024/05/01 13:49:37 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	allocate_memory(t_exec *exec)
{
	exec->pid = (int *)malloc(sizeof(int) * exec->processes);
	if (!exec->pid)
		return (1);
	exec->status = (int *)malloc(sizeof(int) * exec->processes);
	if (!exec->status)
	{
		free(exec->pid);
		return (1);
	}
	exec->open_fds = (int *)malloc(sizeof(int) * exec->processes * 2);
	if (!exec->open_fds)
	{
		free(exec->pid);
		free(exec->status);
		return (1);
	}
	return (0);
}
