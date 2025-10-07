/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:50:14 by mhaizan           #+#    #+#             */
/*   Updated: 2025/10/06 20:58:37 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	line_extractor(char **line, size_t *i)
{
	while ((*line)[*i] && (*line)[*i] != '\n')
		(*i)++;
	if ((*line)[*i] == '\n')
		(*i)++;
}

static char	*extract_line(char **line)
{
	char	*extracted_line;
	char	*temp;
	size_t	i;

	if (**line == '\0')
	{
		if (*line)
			free(*line);
		*line = NULL;
		return (NULL);
	}
	i = 0;
	line_extractor(line, &i);
	extracted_line = ft_substr(*line, 0, i);
	if (!extracted_line)
	{
		free(extracted_line);
		return (NULL);
	}
	temp = ft_strdup(*line + i);
	free(*line);
	*line = temp;
	return (extracted_line);
}

static int	read_to_stash(int fd, char **line)
{
	char	*buf;
	char	*tmp;
	ssize_t	n;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	n = read(fd, buf, BUFFER_SIZE);
	if (n <= 0)
	{
		free(buf);
		return (n);
	}
	buf[n] = '\0';
	tmp = ft_strjoin(*line, buf);
	free(*line);
	*line = tmp;
	free(buf);
	return (n);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	ssize_t		n;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line[fd])
		line[fd] = ft_strdup("");
	n = 1;
	while (!ft_strchr(line[fd], '\n') && n > 0)
		n = read_to_stash(fd, &line[fd]);
	if (n < 0)
	{
		free(line[fd]);
		line[fd] = NULL;
		return (NULL);
	}
	return (extract_line(&line[fd]));
}
