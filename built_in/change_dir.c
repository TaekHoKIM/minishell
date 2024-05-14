/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:57:29 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/12 16:30:55 by minyekim         ###   ########.fr       */
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

void	change_dir(t_token_list *head, t_envp *envp, t_info *info)
{
	char	buf[MAX_PATH];
	char	*path;

	if (info->pipe_cnt > 0)
		return ;
	argv_set(head, info);
	path = getcwd(buf, MAX_PATH);
	if (path == NULL)
	{
		ft_perror("getcwd");
		info->exit_code = 1;
		return ;
	}
	if (info->argv[1] == NULL)
	{
		if (ft_chdir("/Users/minyekim", info) == FAIL)
			return ;
	}
	else
		if (ft_chdir(info->argv[1], info) == FAIL)
			return ;
	old_pwd_set(envp, path);
	pwd_set(envp, info);
}
