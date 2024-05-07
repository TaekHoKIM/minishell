/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:25:01 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/07 21:32:37 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	make_pipe(t_token_list *head, t_info *info)
{
	int	i;

	while (head != NULL)
	{
		if (head->type == PIPE)
			info->pipe_cnt++;
		head = head->next;
	}
	info->pipefd = ft_malloc(sizeof(int *), info->pipe_cnt + 1);
	info->pipefd[info->pipe_cnt] = NULL;
	i = 0;
	while (i < info->pipe_cnt)
	{
		info->pipefd[i] = ft_malloc(sizeof(int), 2);
		if (pipe(info->pipefd[i]) == FAIL)
			return (ft_perror("pipe"));
		i++;
	}
	return (SUCCESS);
}

static int	pipex_initial_settings(t_token_list *head, t_info *info)
{
	if (make_pipe(head, info) == FAIL)
		return (FAIL);
	info->pid = ft_malloc(sizeof(pid_t), info->pipe_cnt + 1);
	signal(SIGINT, SIG_IGN);
	return (SUCCESS);
}

static void	parent_fd_close(int **pipefd, int i, int cmd_cnt)
{
	if (i > 0)
	{
		if (close(pipefd[i - 1][0]) == FAIL)
		{
			ft_perror("close");
			return ;
		}
	}
	if (i + 1 < cmd_cnt)
	{
		if (close(pipefd[i][1]) == FAIL)
		{
			ft_perror("close");
			return ;
		}	
	}
}

static int	pipex(t_token_list *head, t_envp *envp, t_info *info, int i)
{
	if (av_ev_path_file_set(head, envp, info) == FAIL)
		return (SUCCESS);
	info->pid[i] = fork();
	if (info->pid[i] == FAIL)
		return (ft_perror("fork"));
	if (info->pid[i] == 0)
		child_process(info, i);
	else
		parent_fd_close(info->pipefd, i, info->pipe_cnt + 1);
	return (SUCCESS);
}

int	exec_process(t_token_list *head, t_envp *envp, t_info *info)
{
	int		i;

	i = 0;
	if (pipex_initial_settings(head, info) == FAIL)
		return (EXIT_FAILURE);
	while (i < info->pipe_cnt + 1)
	{
		if (pipex(head, envp, info, i) == FAIL)
			return (EXIT_FAILURE);
		while (head != NULL && head->type != PIPE)
			head = head->next;
		if (head != NULL && head->type == PIPE)
			head = head->next;
		i++;
	}
	// wait_exit(pid, cmd_cnt, pipe_info);
	return (SUCCESS);
}
