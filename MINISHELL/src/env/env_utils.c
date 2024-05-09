/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:51:00 by csturm            #+#    #+#             */
/*   Updated: 2024/04/16 15:51:02 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_key(char *cmd, int *j)
{
	while (cmd[*j] && cmd[*j] != '=')
		(*j)++;
	return (ft_substr(cmd, 0, *j));
}

char	*get_value_concat(char *cmd, int *j)
{
	*j = *j + 2;
	while (cmd[*j] && cmd[*j] != ':')
		(*j)++;
	return (ft_substr(cmd, *j, ft_strlen(cmd) - *j));
}

char	*get_value(char *cmd, int *j)
{
	*j = *j + 1;
	return (ft_substr(cmd, *j, ft_strlen(cmd) - *j));
}

char	*ft_getenv(const char *name, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
