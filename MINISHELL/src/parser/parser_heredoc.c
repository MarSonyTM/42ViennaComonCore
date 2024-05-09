/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:49:41 by mafurnic          #+#    #+#             */
/*   Updated: 2024/05/01 11:58:34 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*handle_input_buffer(char *input_buffer,
		char *heredoc_input, t_command *command, int fd)
{
	char	*expanded_input;
	char	*new_heredoc_input;

	expanded_input = expand_variables(input_buffer, command);
	new_heredoc_input = append_line_to_heredoc(heredoc_input, expanded_input);
	write(fd, expanded_input, ft_strlen(expanded_input));
	write(fd, "\n", 1);
	free(heredoc_input);
	free(input_buffer);
	free(expanded_input);
	return (new_heredoc_input);
}

char	*read_and_write_heredoc(int fd, char *delimiter,
			char *heredoc_input, t_command *command)
{
	char	*input_buffer;

	signal(SIGINT, heredoc_sigint_handler);
	g_signal_caught = 0;
	while (1)
	{
		if (g_signal_caught == SIGINT)
		{
			return (close(fd), free(heredoc_input), NULL);
		}
		input_buffer = prompt_and_read_line();
		if (!input_buffer)
			return (close(fd), free(heredoc_input), NULL);
		if (ft_strcmp(input_buffer, delimiter) == 0)
		{
			free(input_buffer);
			break ;
		}
		heredoc_input = handle_input_buffer(input_buffer,
				heredoc_input, command, fd);
	}
	return (heredoc_input);
}

char	*handle_heredoc(t_token **current, t_command *command)
{
	char	*delimiter;
	char	*heredoc_input;
	int		fd;
	char	temp_file_name[30];
	int		temp_file_num;

	temp_file_num = 0;
	ft_strcpy(temp_file_name, "/tmp/minishell_heredoc");
	if (!current || !(*current))
		return (NULL);
	delimiter = (*current)->value;
	heredoc_input = NULL;
	fd = create_temp_file(temp_file_name, temp_file_num);
	if (fd == -1)
		return (NULL);
	heredoc_input = read_and_write_heredoc(fd,
			delimiter, heredoc_input, command);
	if (!heredoc_input)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	free(heredoc_input);
	return (ft_strdup(temp_file_name));
}
