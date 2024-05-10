/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:54:10 by minyekim          #+#    #+#             */
/*   Updated: 2024/05/10 14:41:33 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_envp(t_envp **env, char **envp)
{
	t_envp	*new;
	t_envp	*tmp;
	int		i;

	i = 0;
	while(envp[i] != NULL)
	{
		new = ft_malloc(sizeof(tmp), 1);
		new->line = ft_strdup(envp[i]);
		new->next = NULL;
		if (i == 0)
			*env = new;
		else
		{
			tmp = *env;
			while ((tmp)->next != NULL)
				tmp = tmp->next;
			tmp->next = new;
		}
		i++;
	}
}