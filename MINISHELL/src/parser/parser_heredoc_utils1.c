/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:05:53 by mafurnic          #+#    #+#             */
/*   Updated: 2024/04/28 12:27:37 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_variables(const char *input, t_command *command)
{
	char	*output;

	output = ft_strdup("");
	while (*input)
	{
		if (*input == '$')
			output = expand_variable(&input, output, command);
		else
		{
			output = ft_strjoin_free_char(output, *input);
			input++;
		}
	}
	return (output);
}

char	*append_line_to_heredoc(char *heredoc_input, const char *input_buffer)
{
	char	*temp;
	char	*new_heredoc_input;

	if (heredoc_input)
		temp = ft_strjoin(heredoc_input, "\n");
	else
		temp = ft_strdup("");
	new_heredoc_input = ft_strjoin(temp, input_buffer);
	free(temp);
	return (new_heredoc_input);
}

int	create_temp_file(char *temp_file_name, int temp_file_num)
{
	int	fd;

	while (1)
	{
		fd = open(temp_file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1 && errno == EEXIST)
		{
			temp_file_num++;
			temp_file_name[20] = '0' + temp_file_num;
			continue ;
		}
		else if (fd == -1)
		{
			perror("open");
			return (-1);
		}
		break ;
	}
	return (fd);
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_signal_caught = SIGINT;
	rl_replace_line("", 0);
	rl_on_new_line();
}
