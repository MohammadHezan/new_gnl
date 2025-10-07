/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaizan <mhaizan@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 13:50:36 by mhaizan           #+#    #+#             */
/*   Updated: 2025/10/07 20:03:06 by mhaizan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **line)
{
	char	*extracted_line;
	char	*temp;
	size_t	i;

	if (!*line || **line == '\0')
	{
		if (*line)
			free(*line);
		*line = NULL;
		return (NULL);
	}
	i = 0;
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	if ((*line)[i] == '\n')
		i++;
	extracted_line = ft_substr(*line, 0, i);
	if (!extracted_line)
		return (NULL);
	temp = ft_strdup(*line + i);
	free(*line);
	*line = temp;
	return (extracted_line);
}

static int	read_to_buf(int fd, char **line)
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
	static char	*line;
	ssize_t		n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line)
		line = ft_strdup("");
	n = 1;
	while (n > 0 && !ft_strchr(line, '\n'))
		n = read_to_buf(fd, &line);
	if (n < 0)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	return (extract_line(&line));
}
/* #include <stdio.h>
int	main(void)
{
	char	*l;

	int fd=open("tst.txt", O_RDONLY);
	while((l = get_next_line(fd)))
	{
		printf("%s\n", l);
		free(l);
	}
	close(fd);
}
 */