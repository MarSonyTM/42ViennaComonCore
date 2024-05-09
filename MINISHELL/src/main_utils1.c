/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:36:46 by mafurnic          #+#    #+#             */
/*   Updated: 2024/05/02 15:50:29 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	setup_and_handle_input(t_env **env, t_main_loop *loop)
{
	setup_signals();
	signal(SIGQUIT, SIG_IGN);
	handle_input_and_expansion(env, loop);
	g_signal_caught = 0;
}

int	execute_and_cleanup(t_env **env, t_main_loop *loop)
{
	int	exit_status;
	int	result;

	result = handle_lexer_and_parser(env, loop);
	if (result == 1 && !g_signal_caught)
		exit_status = 127;
	else if (g_signal_caught)
	{
		g_signal_caught = 0;
		printf("signal caught\n");
		exit_status = 130;
	}
	else if (!result)
	{
		free_tokens(&loop->tokens);
		exit_status = executor(loop->cmd, env, loop->exit_status);
		reset_free_cmd(&loop->cmd, loop->input);
	}
	else
		exit_status = 0;
	return (exit_status);
}

int	main_loop(t_env **env)
{
	int			exit_status;
	t_main_loop	loop;

	exit_status = 0;
	loop.exit_status = exit_status;
	while (1)
	{
		setup_and_handle_input(env, &loop);
		loop.exit_status = execute_and_cleanup(env, &loop);
	}
	return (loop.exit_status);
}
