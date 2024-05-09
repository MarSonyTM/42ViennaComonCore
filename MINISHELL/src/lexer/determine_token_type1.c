/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_token_type1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:14:46 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/16 14:45:52 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_command_in_dir(char *dir, char *token)
{
	char	*full_path;
	bool	found;

	full_path = construct_full_path(dir, token);
	found = (access(full_path, F_OK | X_OK) == 0);
	free(full_path);
	return (found);
}

bool	is_command(char *token, t_lexer *lexer)
{
	char	*path;
	char	*path_copy;
	char	*dir;

	path = ft_getenv("PATH", lexer->env);
	if (!path)
		return (false);
	path_copy = ft_strdup(path);
	if (!path_copy)
		return (false);
	dir = ft_strtok(path_copy, ":");
	while (dir)
	{
		if (check_command_in_dir(dir, token))
		{
			free(path_copy);
			return (true);
		}
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (false);
}

char	*construct_full_path(char *dir, char *token)
{
	size_t	full_path_len;
	char	*full_path;

	full_path_len = ft_strlen(dir) + ft_strlen(token) + 2;
	full_path = malloc(full_path_len);
	if (!full_path)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	ft_strcpy(full_path, dir);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, token);
	return (full_path);
}
