/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:51:07 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/08 20:31:19 by minyekim         ###   ########.fr       */
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
	
	info->exit_code = WEXITSTATUS(status);
}