/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:18:40 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/07 20:48:50 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_doc(char *filename, char *limiter)
{
	char	*line;
	int		fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == FAIL)
		return (ft_perror(filename));
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		if (ft_limiter_check(line, limiter) == YES_LIMITER)
			break ;
		write(fd, line, ft_strlen(line));
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

void	find_here_doc_and_process(t_token_list *head, t_info *info)
{
	char	*tmp;
	char	*filename;

	signal(SIGINT, here_doc_child_sigint);
	info->here_doc_cnt = 0;
	while (head != NULL)
	{
		if (head->type == IN_D2_ARG)
			fake_here_doc(head->token);
		if (head->type == IN_OPEN_D2)
		{
			info->here_doc_cnt++;
			tmp = ft_itoa(info->here_doc_cnt);
			filename = ft_strjoin(".temp", tmp);
			free(tmp);	
			if (here_doc(filename, head->token) == FAIL)
				exit(EXIT_FAILURE);
			free(filename);
		}
		head = head->next;
	}
	exit(EXIT_SUCCESS);
}

static void	here_doc_token_name_change(t_token_list *head, t_info *info)
{
	char	*tmp;
	char	*filename;

	info->here_doc_cnt = 0;
	while (head != NULL)
	{
		if (head->type == IN_OPEN_D2)
		{
			info->here_doc_cnt++;
			tmp = ft_itoa(info->here_doc_cnt);
			filename = ft_strjoin(".temp", tmp);
			free(tmp);	
			free(head->token);
			head->token = filename;
		}
		head = head->next;
	}
}

int	here_doc_preprocessor(t_token_list *head, t_info *info)
{
	pid_t	here_doc_child;
	int		status;
	int		here_doc_child_exit_code;

	here_doc_child = fork();
	if (here_doc_child == FAIL)
		return (ft_perror("fork"));
	else if (here_doc_child == CHILD_PID)
		find_here_doc_and_process(head, info);
	signal(SIGINT, here_doc_parent_sigint);
	if (waitpid(here_doc_child, &status, 0) == FAIL)
		return (ft_perror("waitpid"));
	here_doc_child_exit_code = WEXITSTATUS(status);
	info->exit_code = here_doc_child_exit_code;
	if (here_doc_child_exit_code != EXIT_SUCCESS)
		return (FAIL);
	here_doc_token_name_change(head, info);
	return (SUCCESS);
}
