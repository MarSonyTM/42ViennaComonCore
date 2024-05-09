/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:45:34 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/23 16:14:35 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	lexer(char *input, t_token **tokens, t_lexer *lexer)
{
	lexer = malloc(sizeof(t_lexer));
	if (lexer == NULL)
		return (1);
	lexer->i = 0;
	lexer->token_count = 0;
	lexer->buf_index = 0;
	lexer->in_quote = 0;
	lexer->quote_error = false;
	lexer->lexer_error = false;
	if (input == NULL)
		return (2);
	lexer->buffer = malloc((ft_strlen(input) + 1) * sizeof(char));
	if (lexer->buffer == NULL)
		return (1);
	ft_memset(lexer->buffer, 0, ft_strlen(input) + 1);
	process_input_loop(input, &tokens, lexer, &lexer->quote_error);
	return (finalize_lexer(&lexer->buffer,
			&tokens, lexer,
			lexer->quote_error));
}
