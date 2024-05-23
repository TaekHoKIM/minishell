/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:11:28 by taekhkim          #+#    #+#             */
/*   Updated: 2024/05/23 23:24:24 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_envp *envp)
{
	char	pwd[PATH_MAX];
	int		flag;

	flag = 0;
	while (envp != NULL)
	{
		if (envp->line[0] == 'P' && envp->line[1] == 'W'
			&& envp->line[2] == 'D' && envp->line[3] == '=')
		{
			printf("%s\n", envp->line + 4);
			flag = 1;
			break ;
		}
		envp = envp->next;
	}
	if (flag == 0)
	{
		getcwd(pwd, PATH_MAX);
		printf("%s\n", pwd);
	}
	exit(EXIT_SUCCESS);
}
