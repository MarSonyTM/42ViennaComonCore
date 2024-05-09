/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:36:50 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/28 09:20:07 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strjoin_free_char(char *s1, char c)
{
	char	*new_str;
	size_t	i;

	if (!s1)
		return (NULL);
	new_str = malloc(strlen(s1) + 2);
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	free(s1);
	return (new_str);
}

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new_str[i++] = s2[j++];
	new_str[i] = '\0';
	free(s1);
	return (new_str);
}

char	*prompt_and_read_line(void)
{
	ft_putstr_fd("> ", STDOUT_FILENO);
	return (readline(NULL));
}

char	*get_var_name(const char **input)
{
	const char	*start;

	(*input)++;
	start = *input;
	while (**input && (ft_isalnum(**input) || **input == '_'))
		(*input)++;
	return (ft_substr(start, 0, *input - start));
}

char	*expand_variable(const char **input, char *output, t_command *command)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(input);
	var_value = ft_getenv(var_name, *command->env);
	free(var_name);
	if (var_value)
		output = ft_strjoin_free(output, var_value);
	else
		output = ft_strjoin_free(output, "");
	return (output);
}
