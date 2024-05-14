/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:51:07 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/15 02:31:41 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process_wait(t_info *info)
{
	int	i;
	int	status;

	i = 0;
	while (i < info->pipe_cnt + 1)
	{
		waitpid(info->pid[i], &status, 0);
		i++;
	}
	if (i != 0)
	{
		if (WIFSIGNALED(status) == TRUE)
			info->exit_code = 128 + WTERMSIG(status);
		else
			info->exit_code = WEXITSTATUS(status);
		info->last_child_pid = info->pid[i - 1];
	}
	if (info->exit_code == EXIT_SIGINT)
		printf("\n");
	else if (info->exit_code == EXIT_SIGQUIT)
		printf("Quit: 3\n");
}
