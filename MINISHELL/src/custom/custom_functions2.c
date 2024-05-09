/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:50:20 by csturm            #+#    #+#             */
/*   Updated: 2024/05/01 23:13:09 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_for_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_overflow(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (check_for_digit(str) == 0)
		return (1);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	if (ft_strlen(str + i) > 19)
		return (1);
	if (ft_strlen(str + i) == 19 && sign == 1
		&& ft_strncmp(str + i, "9223372036854775807", 19) > 0)
		return (1);
	if (ft_strlen(str + i) == 19 && sign == -1
		&& ft_strncmp(str + i, "9223372036854775808", 19) > 0)
		return (1);
	return (0);
}

static int	handle_arg(char *str, int *exit_code)
{
	int	overflow;

	overflow = check_overflow(str);
	if (!overflow)
	{
		*exit_code = ft_atoi(str);
		while (*exit_code < 0)
			*exit_code = 256 + *exit_code;
		if (*exit_code > 255)
			*exit_code = *exit_code % 256;
	}
	else
	{
		*exit_code = 2;
		error(ERR_NUM, "exit", str, 1);
	}
	return (overflow);
}

int	exit_cmd(t_cmd *cmd, t_env *env, t_exec **exec, int stdout_fd)
{
	int	exit_code;
	int	overflow;

	exit_code = EXIT_SUCCESS;
	overflow = 0;
	if (cmd->cmd_arr[1])
		overflow = handle_arg(cmd->cmd_arr[1], &exit_code);
	if (cmd->cmd_arr[1] && cmd->cmd_arr[2] && !overflow)
		return (error(ERR_ARGS, "exit", NULL, 1), 1);
	clean_up(cmd, env);
	close_and_free(*exec);
	ft_putendl_fd("exit", 1);
	if (stdout_fd != -1)
		close(stdout_fd);
	exit(exit_code);
	return (0);
}
