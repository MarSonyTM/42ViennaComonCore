/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:50:29 by csturm            #+#    #+#             */
/*   Updated: 2024/04/26 13:28:43 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_env_node(t_env **env, t_env *tmp, t_env *prev)
{
	if (prev == NULL)
		*env = tmp->next;
	else
		prev->next = tmp->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	unset_cmd(t_cmd *cmd, t_env **env)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 1;
	while (cmd->cmd_arr[i] != NULL)
	{
		tmp = *env;
		prev = NULL;
		while (tmp != NULL)
		{
			if (ft_strncmp(tmp->key, cmd->cmd_arr[i],
					ft_strlen(cmd->cmd_arr[i]) + 1) == 0)
			{
				free_env_node(env, tmp, prev);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
}

int	execute_custom(t_cmd *cmd, t_env **env, t_exec **exec, int stdout_fd)
{
	if (ft_strncmp(cmd->cmd_arr[0], "echo", 5) == 0)
		echo_cmd(cmd);
	else if (ft_strncmp(cmd->cmd_arr[0], "cd", 3) == 0)
		return (cd_cmd(cmd, *env));
	else if (ft_strncmp(cmd->cmd_arr[0], "pwd", 4) == 0)
		return (pwd_cmd());
	else if (ft_strncmp(cmd->cmd_arr[0], "export", 7) == 0)
		return (export_cmd(cmd, env));
	else if (ft_strncmp(cmd->cmd_arr[0], "unset", 6) == 0)
		unset_cmd(cmd, env);
	else if (ft_strncmp(cmd->cmd_arr[0], "env", 4) == 0)
		return (env_cmd(cmd, *env));
	else if (ft_strncmp(cmd->cmd_arr[0], "exit", 5) == 0)
		return (exit_cmd(cmd, *env, exec, stdout_fd));
	return (0);
}

void	custom_exec(t_cmd *cmd, t_env **env, t_exec **exec, int stdout_fd)
{
	int	result;

	result = execute_custom(cmd, env, exec, stdout_fd);
	if (result == -1)
	{
		clean_up(cmd, *env);
		close_and_free(*exec);
		exit (1);
	}
	cmd->exit_status = result;
}
