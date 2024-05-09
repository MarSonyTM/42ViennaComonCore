/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:34:47 by mafurnic          #+#    #+#             */
/*   Updated: 2024/05/01 11:31:44 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_quotes(t_expansion *exp,
				int *in_single_quote, int *in_double_quote)
{
	if (**exp->cursor == '\"')
	{
		*in_double_quote = !(*in_double_quote);
		*exp->result = append_to_string(*exp->result, "\"");
		(*exp->cursor)++;
		return (1);
	}
	else if (**exp->cursor == '\'')
	{
		*in_single_quote = !(*in_single_quote);
		*exp->result = append_to_string(*exp->result, "'");
		(*exp->cursor)++;
		return (1);
	}
	return (0);
}

void	expand_env_vars(t_env *env,
			t_expansion *exp, char **input, t_main_loop *loop)
{
	int		in_single_quote;
	int		in_double_quote;

	*exp->result = NULL;
	*exp->cursor = *input;
	in_single_quote = 0;
	in_double_quote = 0;
	exp->exit_status = loop->exit_status;
	while (**exp->cursor)
	{
		if (handle_quotes(exp, &in_single_quote, &in_double_quote))
			continue ;
		if (handle_dollar(exp, in_single_quote, in_double_quote, env))
			continue ;
		if (handle_space(exp, in_single_quote, in_double_quote))
			continue ;
		handle_normal_char(exp);
	}
	free(*input);
	*input = *exp->result;
}
