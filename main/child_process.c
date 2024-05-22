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

static int	check_cmd_or_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (FAIL);
		i++;
	}
	if (i == 0)
		return (SUCCESS);
	return (SUCCESS);
}

static int	accsess_and_file(char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK | X_OK) == 0)
	{
		if (stat(path, &path_stat) == FAIL)
		{
			perror("minishell:");
			exit(errno);
		}
		if (S_ISDIR(path_stat.st_mode) == SUCCESS)
			return (SUCCESS);
	}
	return (FAIL);
}

static void	exit_command_not_found(char *cmd)
{
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	exit(127);
}

static void	check_file_or_dir(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == FAIL)
	{
		perror("minishell:");
		exit(errno);
	}
	if (S_ISDIR(path_stat.st_mode) != SUCCESS)
	{
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": is a directory\n", 18);
		exit(126);
	}
	return ;
}

static char	*access_check(char **path, char *cmd)
{
	char	*res;
	char	*tmp;
	ssize_t	i;

	i = 0;
	if (check_cmd_or_path(cmd) == SUCCESS && path != NULL)
	{
		while (path[i] != NULL)
		{
			tmp = ft_strjoin(path[i], "/");
			res = ft_strjoin(tmp, cmd);
			free(tmp);
			if (accsess_and_file(res) == SUCCESS)
				return (res);
			free(res);
			i++;
		}
		exit_command_not_found(cmd);
	}
	if (access(cmd, F_OK | X_OK) == 0)
	{
		check_file_or_dir(cmd);
		return (cmd);
	}
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
