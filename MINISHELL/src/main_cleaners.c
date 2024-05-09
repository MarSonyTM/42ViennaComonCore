/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cleaners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:42:27 by marianfurni       #+#    #+#             */
/*   Updated: 2024/04/30 19:17:35 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_lexer(int lexer_status, t_token **tokens, char **input, t_env *env)
{
	if (lexer_status == 1)
	{
		free_env(env);
		free_tokens(tokens);
		free(*input);
		exit(1);
	}
	else if (lexer_status == 2)
	{
		free_tokens(tokens);
		free(*input);
		return (1);
	}
	return (0);
}

int	handle_parser(int parse_status, t_main_loop *loop, t_env *env)
{
	if (parse_status == 1)
	{
		clean_up(loop->cmd, env);
		free_tokens(&(loop->tokens));
		free(loop->input);
		exit(1);
	}
	else if (parse_status == 2)
	{
		free_cmds(&(loop->cmd));
		free_tokens(&(loop->tokens));
		free(loop->input);
		return (1);
	}
	return (0);
}
