/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:57:29 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/28 17:13:33 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	old_pwd_set(t_envp *envp, char *old_path)
{
	while (envp != NULL)
	{
		if (envp->line[0] == 'O' && envp->line[1] == 'L'
			&& envp->line[2] == 'D' && envp->line[3] == 'P'
			&& envp->line[4] == 'W' && envp->line[5] == 'D'
			&& envp->line[6] == '=')
		{
			free(envp->line);
			envp->line = ft_strjoin("OLDPWD=", old_path);
			break ;
		}
		envp = envp->next;
	}
}

static void	pwd_set(t_envp *envp)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	while (envp != NULL)
	{
		if (envp->line[0] == 'P' && envp->line[1] == 'W'
			&& envp->line[2] == 'D' && envp->line[3] == '=')
		{
			free(envp->line);
			envp->line = ft_strjoin("PWD=", path);
			break ;
		}
		envp = envp->next;
	}
}

static int	change_dir_home_arg(t_envp *envp, t_info *info)
{
	char	*path;

	path = NULL;
	if (info->argv[1][0] == '~')
	{
		if (find_home_path(envp, info) != FAIL)
			path = ft_strjoin(info->home_dir, info->argv[1] + 1);
		else
		{
			if (info->first_home == NULL)
				return (home_not_set());
			else
				path = ft_strjoin(info->first_home, info->argv[1] + 1);
		}
	}
	else
		path = info->argv[1];
	if (ft_chdir(path) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

static int	dir_set(t_envp *envp, t_info *info)
{
	if (info->argv[1] == NULL)
	{
		if (find_home_path(envp, info) == FAIL)
			return (home_not_set());
		return (ft_chdir(info->home_dir));
	}
	if (change_dir_home_arg(envp, info) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	change_dir(t_token_list *head, t_envp *envp, t_info *info)
{
	char	old_path[PATH_MAX];
	char	tmp[PATH_MAX];

	if (info->pipe_cnt > 0)
		return (FAIL);
	argv_set(head, info);
	getcwd(old_path, PATH_MAX);
	if (dir_set(envp, info) == FAIL)
		return (SUCCESS);
	if (getcwd(tmp, PATH_MAX) == NULL)
	{
		write(2, "cd: error retrieving current directory: ", 41);
		perror("getcwd: cannot access parent directories");
	}
	old_pwd_set(envp, old_path);
	pwd_set(envp);
	return (SUCCESS);
}
