/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:42:24 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/04 20:51:06 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_token_list *head, t_envp *envp, t_info *info, int i)
{
	char	*cmd_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	set_terminal_print();
	if (av_ev_path_file_set(head, envp, info) == FAIL)
		exit(EXIT_FAILURE);
	if (i == 0)
		first_command_fd_set(info, i);
	else if (i == info->pipe_cnt)
		last_command_fd_set(info, i);
	else
		middle_command_fd_set(info, i);
	if (info->argv[0] == NULL)
		exit(EXIT_SUCCESS);
	builtin_check_exec(head, envp, info);
	cmd_path = access_check(info->path, info->argv[0]);
	close_fd();
	execve(cmd_path, info->argv, info->envp);
	ft_perror(cmd_path);
	exit(CMD_NOT_FOUND);
}
