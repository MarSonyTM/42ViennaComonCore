/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:56:21 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/28 07:10:31 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_quote_error(char **buffer, t_lexer *lexer, bool quote_error)
{
	if (quote_error)
		return (free(*buffer), free(lexer), 2);
	free(*buffer);
	free(lexer);
	return (0);
}

int	handle_token(char **buffer, t_token ***tokens, t_lexer *lexer)
{
	char	*dup_buffer;

	if ((*buffer)[lexer->buf_index] != '\0')
	{
		(*buffer)[lexer->buf_index] = '\0';
	}
	dup_buffer = ft_strdup(*buffer);
	if (add_token(*tokens,
			determine_token_type(*buffer, lexer), dup_buffer) == 1)
	{
		free(dup_buffer);
		return (free(*buffer), free(lexer), 1);
	}
	free(dup_buffer);
	(lexer->token_count)++;
	return (0);
}

int	finalize_lexer(char **buffer,
		t_token ***tokens, t_lexer *lexer, bool quote_error)
{
	if (lexer->buf_index > 0 && !quote_error)
	{
		if (lexer->in_quote != 0)
		{
			error("Unclosed quote", ERROR, NULL, 0);
			quote_error = true;
		}
		else
		{
			if (handle_token(buffer, tokens, lexer) == 1)
				return (1);
		}
	}
	return (handle_quote_error(buffer, lexer, quote_error));
}
