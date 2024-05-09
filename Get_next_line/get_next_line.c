/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:41:24 by marianfurni       #+#    #+#             */
/*   Updated: 2023/10/14 08:23:28 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buf, char *backup)
{
	int		read_line;
	char	*temp;

	read_line = 1;
	while (read_line != '\0')
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (0);
		else if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*extract_line(char *content)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (content[count] != '\n' && content[count] != '\0')
		count++;
	if (content[count] == '\0' || content[1] == '\0')
		return (0);
	backup = ft_substr(content, count + 1, ft_strlen(content) - count);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	content[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	line = read_line(fd, buf, backup);
	if (!line)
	{
		free(backup);
		backup = NULL;
	}
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	backup = extract_line(line);
	return (line);
}
