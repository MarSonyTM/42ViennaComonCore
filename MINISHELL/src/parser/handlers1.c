/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:05:23 by mafurnic          #+#    #+#             */
/*   Updated: 2024/05/09 21:44:05 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_builtin_or_command_parser(t_command *command)
{
	*command->current_cmd = initialize_new_command(*command->cmd,
			*command->current, *command->env, &command->err_code);
	if (!(*command->current_cmd) && !command->err_code)
		command->err_code = 1;
	*command->arg_count = 1;
}

void	handle_argument(t_cmd *current_cmd, t_token *current, int *err_code)
{
	if (current_cmd == NULL)
	{
		*err_code = 1;
		return ;
	}
	if (add_argument_to_command(current_cmd, current->value) != 0)
		*err_code = 1;
	return ;
}

int	handle_input(t_cmd *current_cmd, t_token *current)
{
	if (!current->next)
	{
		error("\\n", ERR_PARS, NULL, 0);
		return (2);
	}
	current_cmd->input = ft_strdup(current->value);
	if (!current_cmd->input)
		return (1);
	return (0);
}

int	handle_parser_redirection(t_cmd *current_cmd, t_token **current)
{
	int		result;

	if (!(*current)->next)
	{
		error("\\n", ERR_PARS, NULL, 0);
		return (2);
	}
	result = handle_redirection(current_cmd, current, (*current)->type);
	if (result != 0)
		return (result);
	return (0);
}

int	hdl_parser_heredoc(t_cmd **current_cmd,
		t_token **current, t_command *command)
{
	char	*heredoc_input;

	if (!(*current)->next)
	{
		error("\\n", ERR_PARS, NULL, 0);
		return (2);
	}
	*current = (*current)->next;
	heredoc_input = handle_heredoc(current, command);
	if (!heredoc_input)
		return (2);
	if (*current_cmd)
	{
		(*current_cmd)->input = heredoc_input;
		return (0);
	}
	else
	{
		free(heredoc_input);
		return (2);
	}
	return (0);
}
