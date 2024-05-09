/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:50:42 by csturm            #+#    #+#             */
/*   Updated: 2024/05/01 12:08:11 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_env_var(t_env *env_var, char *key, char *value)
{
	free(env_var->key);
	free(env_var->value);
	env_var->key = key;
	env_var->value = value;
}

t_env	*find_env_var(t_env *env, char *key)
{
	while (env != NULL)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	export_cmd(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 1;
	if (!cmd->cmd_arr[1])
		return (env_cmd(cmd, *env), 0);
	if (cmd->cmd_arr[1][0] == '=' || ft_isdigit(cmd->cmd_arr[1][0]))
	{
		error(ERR_ARG, "export", cmd->cmd_arr[1], 1);
		return (1);
	}
	while (cmd->cmd_arr[i])
	{
		if (ft_strchr(cmd->cmd_arr[i], '='))
		{
			if (ft_strchr(cmd->cmd_arr[i], '$')
				&& concatenate_env_var(cmd->cmd_arr[i], env, 0))
				return (-1);
			else if (add_new_env_var(cmd->cmd_arr[i], env, 0) == 1)
				return (-1);
		}
		else if (add_empty_env_var(cmd->cmd_arr[i], env) == 1)
			return (-1);
		i++;
	}
	return (0);
}

int	handle_new_env_var(t_env **env, char *key, char *value)
{
	*env = add_env_node(env, key, value);
	if (!*env)
		return (1);
	return (0);
}

int	handle_existing_env_var(t_env *tmp, char *key, char *value)
{
	tmp->value = ft_strjoin(tmp->value, value);
	free(key);
	free(value);
	return (0);
}
