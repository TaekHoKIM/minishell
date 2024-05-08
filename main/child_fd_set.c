/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_fd_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:26:21 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/08 20:41:50 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_command_fd_set(t_info	*info, int i)
{
	if (info->i_fd == STDIN && info->o_fd == STDOUT &&
		i == info->pipe_cnt)
       		pipe_set(NO_CHANGE, NO_CHANGE);
	else if (info->i_fd == STDIN && info->o_fd == STDOUT)
		pipe_set(NO_CHANGE, info->pipefd[i][1]);
	else if (info->i_fd == STDIN && info->o_fd != STDOUT)
		pipe_set(NO_CHANGE, info->o_fd);
	else if (info->i_fd != STDIN && info->o_fd == STDOUT 
			&& i == info->pipe_cnt)
		pipe_set(info->i_fd, NO_CHANGE);
	else if (info->i_fd != STDIN && info->o_fd != STDOUT)
		pipe_set(info->i_fd, info->o_fd);
}

void	last_command_fd_set(t_info *info, int i)
{
	if (info->i_fd == STDIN && info->o_fd == STDOUT)
        pipe_set(info->pipefd[i - 1][0], NO_CHANGE);
    else if (info->i_fd != STDIN && info->o_fd != STDOUT)
        pipe_set(info->i_fd, info->o_fd);
    else if (info->i_fd != STDIN && info->o_fd == STDOUT)
        pipe_set(info->i_fd, NO_CHANGE);
    else if (info->i_fd == STDIN && info->o_fd != STDOUT)
        pipe_set(info->pipefd[i - 1][0], info->o_fd);
}

void	middle_command_fd_set(t_info *info, int i)
{
	if (info->i_fd == STDIN && info->o_fd == STDOUT)
        pipe_set(info->pipefd[i - 1][0], info->pipefd[i][1]);
    else if (info->i_fd == STDIN && info->o_fd != STDOUT)
        pipe_set(info->pipefd[i - 1][0], info->o_fd);
    else if (info->i_fd != STDIN && info->o_fd == STDOUT)
        pipe_set(info->i_fd, info->pipefd[i][1]);
    else if (info->i_fd != STDIN && info->o_fd != STDOUT)
        pipe_set(info->i_fd, info->o_fd);
}
