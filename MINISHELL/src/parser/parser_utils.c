/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:04:35 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/18 18:38:18 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*initialize_new_command(t_cmd **cmd,
				t_token *current_token, t_env *env, int *err_code)
{
	t_cmd	*new_cmd;

	new_cmd = new_command(cmd);
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_arr[0] = ft_strdup(current_token->value);
	if (!new_cmd->cmd_arr[0])
		return (NULL);
	new_cmd->cmd_arr[1] = NULL;
	if (current_token->type == TOKEN_COMMAND)
	{
		new_cmd->cmd_path = resolve_command_path
			(current_token->value, env, err_code);
		if (!new_cmd->cmd_path)
			return (NULL);
	}
	else
	{
		new_cmd->cmd_path = NULL;
	}
	return (new_cmd);
}

int	add_argument_to_command(t_cmd *current_cmd, const char *arg_value)
{
	int		arg_count;
	char	**temp;

	if (current_cmd == NULL || arg_value == NULL)
		return (1);
	arg_count = 0;
	while (current_cmd->cmd_arr[arg_count] != NULL)
	{
		arg_count++;
	}
	temp = realloc(current_cmd->cmd_arr, sizeof(char *) * (arg_count + 2));
	if (!temp)
		return (1);
	current_cmd->cmd_arr = temp;
	current_cmd->cmd_arr[arg_count] = ft_strdup(arg_value);
	if (current_cmd->cmd_arr[arg_count] == NULL)
		return (1);
	current_cmd->cmd_arr[arg_count + 1] = NULL;
	return (0);
}

int	handle_exit_status(t_cmd *current_cmd, t_token *current)
{
	if (current_cmd == NULL)
		return (0);
	current_cmd->exit_status_token = ft_strdup(current->value);
	if (!current_cmd->exit_status_token)
		return (1);
	return (0);
}
