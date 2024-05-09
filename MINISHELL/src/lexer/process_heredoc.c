/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:26:16 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/16 18:04:56 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	process_heredoc(char **buffer,
	t_token ***tokens, t_lexer *lexer)
{
	char	*tmp_buffer;
	char	*tmp;

	lexer->in_quote = 0;
	if (lexer->buf_index > 0)
	{
		(*buffer)[lexer->buf_index] = '\0';
		tmp_buffer = ft_strdup(*buffer);
		if (add_token(*tokens,
				determine_token_type(*buffer, lexer),
				tmp_buffer) == 1)
			return (free(tmp_buffer), 1);
		lexer->buf_index = 0;
		(lexer->token_count)++;
		free(tmp_buffer);
	}
	tmp = ft_strdup("<<");
	if (add_token(*tokens, TOKEN_HEREDOC, tmp) == 1)
		return (free(tmp), 1);
	(lexer->token_count)++;
	(lexer->i)++;
	free(tmp);
	return (0);
}
