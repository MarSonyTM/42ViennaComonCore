/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_token_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:06:07 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/18 12:58:53 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token_type	determine_token_type(char *token,
				t_lexer *lexer)
{
	if (lexer->token_count == 0)
		return (handle_first_token(token, lexer));
	return (handle_subsequent_tokens(token, lexer));
}

t_token_type	handle_first_token(char *token, t_lexer *lexer)
{
	int			i;
	char		*builtins[8];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(token, builtins[i]) == 0)
		{
			(lexer->token_count)++;
			return (TOKEN_BUILTIN);
		}
		i++;
	}
	(lexer->token_count)++;
	return (TOKEN_COMMAND);
}

t_token_type	handle_subsequent_tokens(char *token,
				t_lexer *lexer)
{
	t_token_type	special_token;

	special_token = check_special_tokens(token);
	if (special_token != TOKEN_ARG)
		return (special_token);
	if (lexer->token_count == 0 && is_command(token, lexer))
		return (TOKEN_COMMAND);
	if (token[0] == '$' && token[1] != '\0')
		return (handle_dollar_tokens(token, lexer));
	return (TOKEN_ARG);
}

t_token_type	check_special_tokens(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(token, "<") == 0)
		return (TOKEN_REDIRECT_IN);
	if (ft_strcmp(token, ">") == 0)
		return (T_R_OT);
	if (ft_strcmp(token, ">>") == 0)
		return (T_R_OUT_A);
	if (ft_strcmp(token, "<<") == 0)
		return (TOKEN_HEREDOC);
	if (ft_strcmp(token, ",") == 0)
		return (TOKEN_COMMA);
	if (ft_strcmp(token, "..") == 0)
		return (TOKEN_ARG);
	return (TOKEN_ARG);
}

t_token_type	handle_dollar_tokens(char *token, t_lexer *lexer)
{
	if (lexer->in_quote == 2 || lexer->in_quote == 1)
		return (TOKEN_ARG);
	if (ft_strcmp(token, "$?") == 0)
		return (TOKEN_EXIT_STATUS);
	return (TOKEN_ARG);
}
