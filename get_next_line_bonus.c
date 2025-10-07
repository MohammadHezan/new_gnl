#include "get_next_line_bonus.h"

static char	*extract_line(char **line)
{
	char	*extracted;
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
	while ((*line)[i] && (*line)[i] != '\n')
		i++;
	if ((*line)[i] == '\n')
		i++;
	extracted = ft_substr(*line, 0, i);
	if (!extracted)
		return (NULL);
	temp = ft_strdup(*line + i);
	free(*line);
	*line = temp;
	return (extracted);
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
	static char	*line[1024];
	ssize_t		n;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!line[fd])
		line[fd] = ft_strdup("");
	n = 1;
	while (n > 0 && !ft_strchr(line[fd], '\n'))
		n = read_to_buf(fd, &line[fd]);
	if (n < 0)
	{
		free(line[fd]);
		line[fd] = NULL;
		return (NULL);
	}
	if (n == 0 && (!line[fd] || *line[fd] == '\0'))
	{
		free(line[fd]);
		line[fd] = NULL;
		return (NULL);
	}
	return (extract_line(&line[fd]));
}
