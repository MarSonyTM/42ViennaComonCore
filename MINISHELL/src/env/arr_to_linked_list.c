/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_to_linked_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:50:50 by csturm            #+#    #+#             */
/*   Updated: 2024/04/24 17:28:19 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

t_env	*create_env_node(char *envp, int *j)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = get_key(envp, j);
	if (!new->key)
	{
		free(new);
		return (NULL);
	}
	new->value = get_value(envp, j);
	if (!new->value)
	{
		free(new->key);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

static void	check_for_shlvl(t_env *env)
{
	char	*old_value;

	if (ft_strncmp(env->key, "SHLVL", 6) == 0)
	{
		old_value = env->value;
		if (ft_atoi(env->value) < 0)
			env->value = ft_strdup("0");
		else
			env->value = ft_itoa(ft_atoi(env->value) + 1);
		free(old_value);
	}
}

t_env	*arr_to_linked_list(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;
	int		j;

	j = 0;
	env = create_env_node(envp[0], &j);
	if (!env)
		exit (1);
	tmp = env;
	i = 1;
	while (envp[i] != NULL)
	{
		j = 0;
		tmp->next = create_env_node(envp[i], &j);
		if (!tmp->next)
		{
			free_env(env);
			exit (1);
		}
		check_for_shlvl(tmp->next);
		tmp = tmp->next;
		i++;
	}
	return (env);
}
