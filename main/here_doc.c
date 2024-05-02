/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:18:40 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/02 21:28:53 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_file_unlink(int here_doc_cnt)
{
	int		cnt;
	char	*filename;
	char	*tmp;
	
	cnt = 1;
	while (cnt <= here_doc_cnt)
	{
		tmp = ft_itoa(cnt);
		filename = ft_strjoin(".temp", tmp);
		unlink(filename);
		free(tmp);
		free(filename);
		cnt++;
	}
}

static int	ft_limiter_check(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (NO_LIMITER);
		i++;
	}
	return (YES_LIMITER);
}

int	here_doc(char *filename, char *limiter)
{
	char	*line;
	int		fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == FAIL)
	{
		perror(filename);
		return (FAIL);
	}
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (ft_limiter_check(line, limiter) == YES_LIMITER)
			break ;
		if (write(fd, line, ft_strlen(line)) == FAIL)
		{
			perror("write");
			return (FAIL);
		}
		free(line);
	}
	free(line);
	close(fd);
	return (SUCCESS);
}

void	fake_here_doc(char *limiter)
{
	char	*line;

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (ft_limiter_check(line, limiter) == YES_LIMITER)
			break ;
		free(line);
	}
	free(line);
}
