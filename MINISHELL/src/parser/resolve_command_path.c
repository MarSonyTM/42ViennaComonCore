/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_command_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:53:44 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/30 15:37:13 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*create_full_path(char *dir, char *command,
		size_t dirLen, size_t commandLen)
{
	char	*full_path;

	full_path = malloc(dirLen + commandLen + 2);
	if (full_path == NULL)
	{
		return (NULL);
	}
	ft_strcpy(full_path, dir);
	full_path[dirLen] = '/';
	ft_strcpy(full_path + dirLen + 1, command);
	return (full_path);
}

static bool	is_command_found(char *fullPath)
{
	return (access(fullPath, F_OK) == 0 && access(fullPath, X_OK) == 0);
}

static char	*find_command_in_path(char *command,
				char *pathCopy, size_t commandLen, int *err_code)
{
	char	*dir;
	size_t	dir_len;
	char	*full_path;

	dir = ft_strtok(pathCopy, ":");
	while (dir != NULL)
	{
		dir_len = ft_strlen(dir);
		full_path = create_full_path(dir, command, dir_len, commandLen);
		if (full_path == NULL)
		{
			return (NULL);
		}
		if (is_command_found(full_path))
		{
			return (full_path);
		}
		free(full_path);
		dir = ft_strtok(NULL, ":");
	}
	*err_code = 2;
	return (NULL);
}

char	*resolve_command_path(char *command, t_env *env, int *err_code)
{
	char	*path;
	char	*path_copy;
	size_t	command_len;
	char	*full_path;

	if (is_command_found(command))
		return (ft_strdup(command));
	path = ft_getenv("PATH", env);
	if (!path)
	{
		error(ERR_CMD, command, NULL, 0);
		*err_code = 2;
		return (NULL);
	}
	path_copy = ft_strdup(path);
	if (!path_copy)
		return (NULL);
	command_len = ft_strlen(command);
	full_path = find_command_in_path(command, path_copy, command_len, err_code);
	free(path_copy);
	if (full_path != NULL)
		return (full_path);
	error(ERR_CMD, command, NULL, 0);
	return (NULL);
}
