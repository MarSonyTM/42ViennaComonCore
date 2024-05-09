/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 13:32:28 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/16 18:02:13 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	process_single_redirect_out(char *buffer,
	t_token ***tokens, t_lexer *lexer)
{
	char	*tmp_buffer;
	char	*tmp;

	lexer->in_quote = 0;
	if (lexer->buf_index > 0)
	{
		buffer[lexer->buf_index] = '\0';
		tmp_buffer = ft_strdup(buffer);
		if (add_token(*tokens,
				determine_token_type(buffer, lexer),
				tmp_buffer) == 1)
			return (free(tmp_buffer), 1);
		lexer->buf_index = 0;
		free(tmp_buffer);
	}
	tmp = ft_strdup(">");
	if (add_token(*tokens, T_R_OT, tmp) == 1)
		return (free(tmp), 1);
	(lexer->token_count)++;
	free(tmp);
	return (0);
}

int	process_redirect_out_append(char *buffer,
	t_token ***tokens, t_lexer *lexer)
{
	char	*tmp_buffer;
	char	*tmp;

	if (lexer->buf_index > 0)
	{
		buffer[lexer->buf_index] = '\0';
		tmp_buffer = ft_strdup(buffer);
		if (add_token(*tokens,
				determine_token_type(buffer, lexer),
				tmp_buffer) == 1)
			return (free(tmp_buffer), 1);
		lexer->buf_index = 0;
		free(tmp_buffer);
	}
	tmp = ft_strdup(">>");
	if (add_token(*tokens, T_R_OUT_A, tmp) == 1)
		return (free(tmp), 1);
	(lexer->token_count)++;
	(lexer->i)++;
	free(tmp);
	return (0);
}

// Helper function to process single character redirection "<"
int	process_single_redirect_in(char *buffer,
	t_token ***tokens, t_lexer *lexer)
{
	char	*tmp_buffer;
	char	*tmp;

	if (lexer->buf_index > 0)
	{
		buffer[lexer->buf_index] = '\0';
		tmp_buffer = ft_strdup(buffer);
		if (add_token(*tokens,
				determine_token_type(buffer, lexer),
				tmp_buffer) == 1)
			return (free(tmp_buffer), 1);
		lexer->buf_index = 0;
		free(tmp_buffer);
	}
	tmp = ft_strdup("<");
	if (add_token(*tokens, TOKEN_REDIRECT_IN, tmp) == 1)
		return (free(tmp), 1);
	(lexer->token_count)++;
	free(tmp);
	return (0);
}
