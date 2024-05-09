/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_to_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:51:08 by csturm            #+#    #+#             */
/*   Updated: 2024/04/19 14:16:07 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_len(t_env *env)
{
	t_env	*tmp;	
	int		len;

	len = 0;
	tmp = env;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	*convert_one_node(t_env *env)
{
	char	*tmp_str;
	char	*entry;

	tmp_str = ft_strjoin(env->key, "=");
	if (!tmp_str)
		return (NULL);
	entry = ft_strjoin(tmp_str, env->value);
	free(tmp_str);
	return (entry);
}

char	**allocate_envp(t_cmd *cmd, t_env **env, int len)
{
	char	**envp;

	envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!envp)
	{
		clean_up(cmd, *env);
		return (NULL);
	}
	return (envp);
}

char	**env_to_array(t_cmd *cmd, t_env **env)
{
	t_env	*tmp;	
	char	**envp;
	int		i;
	int		len;

	i = 0;
	len = get_len(*env);
	tmp = *env;
	envp = allocate_envp(cmd, env, len);
	if (!envp)
		return (NULL);
	while (tmp != NULL)
	{
		envp[i] = convert_one_node(tmp);
		if (!envp[i])
		{
			clean_up(cmd, *env);
			free_array(envp);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
