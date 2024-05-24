/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_sub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:44:36 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/24 15:46:53 by taekhkim         ###   ########.fr       */
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

	if (access(path, F_OK | X_OK) == SUCCESS)
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
	exit(CMD_NOT_FOUND);
}

static char	*check_file_or_dir(char *path)
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
		exit(DIRECTORY);
	}
	if (access(path, X_OK) != SUCCESS)
	{
		ft_perror(path);
		exit(DIRECTORY);
	}
	return (path);
}

char	*access_check(char **path, char *cmd)
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
	if (access(cmd, F_OK) == SUCCESS)
		return (check_file_or_dir(cmd));
	ft_perror(cmd);
	exit(CMD_NOT_FOUND);
}
