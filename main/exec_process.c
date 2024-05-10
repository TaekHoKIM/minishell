/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:25:01 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/11 03:08:31 by minyekim         ###   ########.fr       */
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

// The condition 'fd != dir->__dd_fd' works on Mac but not on Linux. 
// To make it work on Linux as well,
// it should be changed to 'fd != *(int *)dir'.
// This change works because the 
// file descriptor (fd) is stored in the first 4 bytes.
// However, this method is quite dangerous.
// It is said to compromise portability.
void	close_fd(void)
{
	DIR				*dir;
	struct dirent	*ent;
	int				fd;
	
	dir = opendir("/dev/fd");
	if (dir == NULL)
		ft_perror("opendir");
	ent = readdir(dir);
	while (ent != NULL)
	{
		fd = atoi(ent->d_name);
		if (fd > STDERR_FILENO && fd != dir->__dd_fd)
			close(fd);
		ent = readdir(dir);
	}
}

void exec_process(t_token_list *head, t_envp *envp, t_info *info)
{
    int     i;
    i = 0;
   if (make_pipe(head, info) == FAIL)
		return ;
	info->pid = ft_malloc(sizeof(pid_t), info->pipe_cnt + 1);
	signal(SIGINT, SIG_IGN);
    while (i < info->pipe_cnt + 1)
    {
		info->pid[i] = fork();
		if (info->pid[i] == FAIL)
		{
			ft_perror("fork");
			return ;
		}
		if (info->pid[i] == 0)
			child_process(head, envp, info, i);
        while (head != NULL && head->type != PIPE)
            head = head->next;
        if (head != NULL && head->type == PIPE)
            head = head->next;
        i++;
    }
	close_fd();
    child_process_wait(info);
}
