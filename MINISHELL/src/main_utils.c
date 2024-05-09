/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:31:59 by mafurnic          #+#    #+#             */
/*   Updated: 2024/05/01 13:34:05 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_cmds(t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*temp;

	current = *cmd;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->cmd_path);
		free_array(temp->cmd_arr);
		free_array(temp->env_vars);
		free(temp->input);
		free(temp->output);
		free(temp->redirection_append);
		free(temp);
	}
	*cmd = NULL;
}

void	reset_free_cmd(t_cmd **cmd, char *input)
{
	t_cmd	*current;

	current = *cmd;
	while (current != NULL)
	{
		if (current->input)
			free(current->input);
		current->input = NULL;
		if (current->output)
			free(current->output);
		current->output = NULL;
		if (current->redirection_append)
			free(current->redirection_append);
		current->redirection_append = NULL;
		if (current->cmd_path)
			free(current->cmd_path);
		current->cmd_path = NULL;
		current = current->next;
	}
	free(input);
	free_cmds(cmd);
}

void	check_args(int argc, char **argv)
{
	if (argc > 1 || argv[1] != NULL)
	{
		error("this program does not take any arguments", "minishell", NULL, 0);
		exit(1);
	}
}

void	init_env_signals(t_env **env, char **envp)
{
	if (envp == NULL || *envp == NULL)
		*env = NULL;
	else
	{
		*env = arr_to_linked_list(envp);
		if (!*env)
			exit(1);
	}
}
