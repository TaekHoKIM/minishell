/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:57:29 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/20 19:23:45 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	old_pwd_set(t_envp *envp, char *pwd)
{
	while (envp != NULL)
	{
		if (envp->line[0] == 'O' && envp->line[1] == 'L'
			&& envp->line[2] == 'D' && envp->line[3] == 'P'
			&& envp->line[4] == 'W' && envp->line[5] == 'D'
			&& envp->line[6] == '=')
		{
			free(envp->line);
			envp->line = ft_strjoin("OLDPWD=", pwd);
			break ;
		}
		envp = envp->next;
	}
}

static void	pwd_set(t_envp *envp, t_info *info)
{
	char	buf[MAX_PATH];
	char	*path;

	path = getcwd(buf, MAX_PATH);
	if (path == NULL)
	{
		ft_perror("getcwd");
		info->exit_code = 1;
		return ;
	}
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

static int	change_dir_hame_arg(t_envp *envp, t_info *info)
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
	if (ft_chdir(path, info) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

static int	dir_set(t_envp *envp, t_info *info)
{
	if (info->argv[1] == NULL)
	{
		if (find_home_path(envp, info) == FAIL)
			return (home_not_set());
		return (ft_chdir(info->home_dir, info));
	}
	if (change_dir_hame_arg(envp, info) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	change_dir(t_token_list *head, t_envp *envp, t_info *info)
{
	char	buf[MAX_PATH];
	char	*old_path;

	if (info->pipe_cnt > 0)
		return (FAIL);
	argv_set(head, info);
	old_path = getcwd(buf, MAX_PATH);
	if (old_path == NULL)
	{
		ft_perror("getcwd");
		info->exit_code = 1;
		return (SUCCESS);
	}
	if (dir_set(envp, info) == FAIL)
		return (SUCCESS);
	old_pwd_set(envp, old_path);
	pwd_set(envp, info);
	return (SUCCESS);
}
