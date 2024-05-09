/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:04:35 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/10 16:29:53 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_error(t_token **current)
{
	if (!(*current) || !(*current)->value)
	{
		error(ERR_PARS, "\n", NULL, 0);
		return (2);
	}
	return (0);
}

static int	handle_input_redirection(t_cmd *current_cmd, t_token **current)
{
	current_cmd->input = ft_strdup((*current)->value);
	if (!current_cmd->input)
		return (1);
	return (0);
}

static int	handle_append_redirection(t_cmd *current_cmd, t_token **current)
{
	current_cmd->redirection_append = ft_strdup((*current)->value);
	if (!current_cmd->redirection_append)
		return (1);
	return (0);
}

static int	handle_output_redirection(t_cmd *current_cmd, t_token **current)
{
	current_cmd->output = ft_strdup((*current)->value);
	if (!current_cmd->output)
		return (1);
	return (0);
}

int	handle_redirection(t_cmd *current_cmd, t_token **current, int current_type)
{
	int	result;

	if (!current_cmd)
	{
		if ((*current)->type == TOKEN_REDIRECT_IN)
			return (error (ERR_FIL, (*current)->next->value, NULL, 1), 2);
		else if ((*current)->type == T_R_OUT_A)
			return (2);
		else if ((*current)->type == T_R_OT)
			return (2);
	}
	if (!current || !(*current))
		return (1);
	*current = (*current)->next;
	result = handle_error(current);
	if (result != 0)
		return (result);
	if (current_type == TOKEN_REDIRECT_IN)
		return (handle_input_redirection(current_cmd, current));
	else if (current_type == T_R_OUT_A)
		return (handle_append_redirection(current_cmd, current));
	else if (current_type == T_R_OT)
		return (handle_output_redirection(current_cmd, current));
	return (0);
}
