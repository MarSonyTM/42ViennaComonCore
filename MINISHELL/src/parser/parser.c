/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:53:08 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/22 15:39:15 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Main parse function
int	parse(t_token *tokens, t_cmd **cmd, t_env *env)
{
	if (!tokens)
		return (2);
	return (process_tokens(tokens, cmd, env));
	return (0);
}

int	process_tokens(t_token *tokens, t_cmd **cmd, t_env *env)
{
	t_command	command;
	t_cmd		*current_cmd;
	int			arg_count;
	t_token		*current;

	current_cmd = NULL;
	arg_count = 0;
	current = tokens;
	command.current = &current;
	command.current_cmd = &current_cmd;
	command.cmd = &cmd;
	command.env = &env;
	command.arg_count = &arg_count;
	command.err_code = 0;
	while (current != NULL)
	{
		process_token(&command);
		if (command.err_code != 0)
			return (command.err_code);
		if (!current_cmd)
			return (1);
		current = current->next;
	}
	return (0);
}
