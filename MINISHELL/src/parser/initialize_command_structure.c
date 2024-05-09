/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_command_structure.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:48:45 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/15 20:37:08 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_cmd	*initialize_command_structure(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd_path = NULL;
	cmd->cmd_arr = malloc(sizeof(char *) * 2);
	if (!cmd->cmd_arr)
		return (NULL);
	cmd->cmd_arr[0] = NULL;
	cmd->input = NULL;
	cmd->exit_status_token = NULL;
	cmd->env_vars = malloc(sizeof(char *));
	if (!cmd->env_vars)
		return (NULL);
	cmd->env_vars[0] = NULL;
	cmd->output = NULL;
	cmd->exit_status = 0;
	cmd->next = NULL;
	cmd->redirection_append = NULL;
	return (cmd);
}

void	link_command_to_list(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (*cmd_list == NULL)
		*cmd_list = new_cmd;
	else
	{
		last = *cmd_list;
		while (last->next != NULL)
			last = last->next;
		last->next = new_cmd;
	}
}

t_cmd	*new_command(t_cmd **cmd)
{
	t_cmd	*new_cmd;

	new_cmd = initialize_command_structure();
	if (!new_cmd || !new_cmd->cmd_arr || !new_cmd->env_vars)
	{
		if (new_cmd)
		{
			if (new_cmd->cmd_arr)
				free(new_cmd->cmd_arr);
			if (new_cmd->env_vars)
				free(new_cmd->env_vars);
			free(new_cmd);
		}
		return (NULL);
	}
	link_command_to_list(cmd, new_cmd);
	return (new_cmd);
}
