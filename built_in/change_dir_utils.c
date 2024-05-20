/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:31:57 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/20 18:51:29 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int home_not_set()
{
	ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	return (FAIL);
}

int	find_home_path(t_envp *envp, t_info *info)
{
	info->home_dir = NULL;
	while (envp != NULL)
	{
		if (envp->line[0] == 'H' && envp->line[1] == 'O'
			&& envp->line[2] == 'M' && envp->line[3] == 'E'
			&& envp->line[4] == '=')
			info->home_dir = envp->line + 5;
		envp = envp->next;
	}
	if (info->home_dir == NULL)
		return (FAIL);
	return (SUCCESS);
}