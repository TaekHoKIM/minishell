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

void	pipe_set(int i_fd, int o_fd)
{
	if (i_fd != NO_CHANGE && dup2(i_fd, STDIN_FILENO) == FAIL)
	{
		ft_perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (o_fd != NO_CHANGE && dup2(o_fd, STDOUT_FILENO) == FAIL)
	{
		ft_perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (i_fd != NO_CHANGE && close(i_fd) == FAIL)
	{
		ft_perror("close");
		exit(EXIT_FAILURE);
	}
	if (o_fd != NO_CHANGE && close(o_fd) == FAIL)
	{
		ft_perror("close");
		exit(EXIT_FAILURE);
	}
}

static char	*access_check(char **path, char *cmd)
{
	char	*res;
	char	*tmp;
	ssize_t	i;

	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		res = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(res, F_OK | X_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	return (cmd);
}

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
