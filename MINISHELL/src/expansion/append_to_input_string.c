/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_to_input_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:32:46 by marianfurni       #+#    #+#             */
/*   Updated: 2024/04/30 17:53:40 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*append_to_string(char *str, const char *append)
{
	char	*new_str;
	size_t	str_len;
	size_t	append_len;

	if (str)
		str_len = ft_strlen(str);
	else
		str_len = 0;
	if (append)
		append_len = ft_strlen(append);
	else
		append_len = 0;
	new_str = malloc(str_len + append_len + 1);
	if (new_str == NULL)
		return (NULL);
	if (str)
		ft_strcpy(new_str, str);
	if (append)
		ft_strcpy(new_str + str_len, append);
	new_str[str_len + append_len] = '\0';
	free(str);
	return (new_str);
}

char	*get_env_value(char *var_name, t_env *env)
{
	t_env	*current_env;

	current_env = env;
	while (current_env != NULL)
	{
		if (ft_strcmp(current_env->key, var_name) == 0)
		{
			return (ft_strdup(current_env->value));
		}
		current_env = current_env->next;
	}
	return (NULL);
}
