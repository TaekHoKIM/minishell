/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:55:47 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/02 21:00:55 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*new_backup(char *line)
{
	size_t	i;
	size_t	len;
	size_t	j;
	char	*temp;

	i = 0;
	j = 0;
	temp = line;
	len = ft_strlen(line);
	while (temp[i] != '\n' && temp[i] != '\0')
		i++;
	if (temp[i] == '\0' || (temp[i] == '\n' && temp[i + 1] == '\0'))
	{
		free(line);
		return (NULL);
	}
	line = (char *)malloc(sizeof(char) * (len - i + 1));
	if (line == NULL)
		exit(EXIT_FAILURE);
	while (i < len)
		line[j++] = temp[++i];
	line[j] = '\0';
	free(temp);
	return (line);
}

char	*line_cut(char *line)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' && i != 0)
		result = (char *)malloc(sizeof(char) * (i + 1));
	else if (line[i] == '\n')
		result = (char *)malloc(sizeof(char) * (++i + 1));
	else
		result = NULL;
	if (result == NULL)
		exit(EXIT_FAILURE);
	while (j < i)
	{
		result[j] = line[j];
		j++;
	}
	if (j != 0)
		result[j] = '\0';
	return (result);
}

static char	*read_file(char *buff, char *line, int fd, ssize_t rd_size)
{
	char	*tmp;

	if (find_enter(line) == SUCCESS)
		return (line);
	while (1)
	{
		rd_size = read(fd, buff, OPEN_MAX - 1);
		if (rd_size == FAIL)
			exit(EXIT_FAILURE);
		else if (rd_size == 0)
			break ;
		buff[rd_size] = '\0';
		if (line == NULL)
			line = ft_strdup("");
		tmp = line;
		line = ft_strjoin(tmp, buff);
		free(tmp);
		if (find_enter(line) == SUCCESS)
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		buff[OPEN_MAX];
	char		*result;
	ssize_t		rd_size;

	result = NULL;
	rd_size = 0;
	line = read_file(buff, line, fd, rd_size);
	if (line == NULL)
		return (NULL);
	result = line_cut(line);
	if (result == NULL)
	{
		free(line);
		return (NULL);
	}
	line = new_backup(line);
	return (result);
}