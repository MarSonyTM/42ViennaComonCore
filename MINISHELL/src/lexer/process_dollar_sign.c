/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dollar_sign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:29:15 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/23 15:39:39 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	finalize_buffer_and_add_token(char **buffer,
	t_token ***tokens,
	t_lexer *lexer, char *tokenValue)
{
	char	*tmp_buffer;
	char	*tmp_token_value;

	if (lexer->buf_index > 0)
	{
		(*buffer)[lexer->buf_index] = '\0';
		tmp_buffer = ft_strdup(*buffer);
		add_token(*tokens,
			determine_token_type(*buffer, lexer),
			tmp_buffer);
		lexer->buf_index = 0;
		free(tmp_buffer);
	}
	if (tokenValue != NULL)
	{
		tmp_token_value = ft_strdup(tokenValue);
		if (add_token(*tokens,
				determine_token_type(tokenValue, lexer),
				tmp_token_value) == 1)
			return (free(tmp_token_value), 1);
		free(tmp_token_value);
	}
	(lexer->token_count)++;
	return (0);
}

void	process_dollar_conditions(char *input, char **buffer,
		t_token ***tokens, t_lexer *lexer)
{
	if (input[lexer->i + 1] == '?')
	{
		finalize_buffer_and_add_token(buffer,
			tokens, lexer, "$?");
		lexer->i += 1;
	}
	else if (input[lexer->i + 1] == '\0' || !ft_isalpha(input[lexer->i + 1]))
	{
		(*buffer)[(lexer->buf_index)++] = input[lexer->i];
	}
	else
	{
		(*buffer)[(lexer->buf_index)++] = input[lexer->i];
	}
}
